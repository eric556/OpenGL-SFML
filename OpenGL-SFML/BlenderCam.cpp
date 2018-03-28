#include "BlenderCam.h"

BlenderCam::BlenderCam()
{
    m_Position = glm::vec3(0.0,0.0,0.0);
    m_ViewDir = glm::vec3(0.0, 0.0, -1.0);
    m_RightVec = glm::vec3(1.0, 0.0, 0.0);
    m_UpVec = glm::vec3(0.0, 1.0, 0.0);

    m_RotatedX = m_RotatedY = m_RotatedZ = 0;
}

void BlenderCam::Move(glm::vec3 direction)
{
    m_Position += direction;
}

void BlenderCam::RotateX(float angle)
{
    m_RotatedX += angle;
    m_ViewDir = glm::normalize((m_ViewDir * std::cosf(angle * (PI / 180.f)) + (m_UpVec * std::sinf(angle * (PI / 180.f)))));

    m_UpVec = glm::cross(m_ViewDir, m_RightVec) * -1.f;
}

void BlenderCam::RotateY(float angle)
{
    m_RotatedY += angle;
    m_ViewDir = glm::normalize((m_ViewDir * std::cosf(angle * (PI / 180.f)) + (m_RightVec * std::sinf(angle * (PI / 180.f)))));

    m_RightVec = glm::cross(m_ViewDir, m_UpVec);
}

void BlenderCam::RotateZ(float angle)
{
    m_RotatedZ += angle;
    m_ViewDir = glm::normalize((m_RightVec * std::cosf(angle * (PI / 180.f)) + (m_UpVec * std::sinf(angle * (PI / 180.f)))));

    m_UpVec = glm::cross(m_ViewDir, m_RightVec) * -1.f;
}

void BlenderCam::MoveForward(float distance)
{
    m_Position += m_ViewDir * distance;
}

void BlenderCam::MoveUpward(float distance)
{
    m_Position += m_UpVec * distance;
}

void BlenderCam::StrafeRight(float distance)
{
    m_Position += m_RightVec * distance;
}

glm::mat4 BlenderCam::GetViewMatrix()
{
    glm::vec3 viewPoint = m_Position + m_ViewDir;
    return glm::lookAt(m_Position, viewPoint, m_UpVec);
}

glm::vec3 BlenderCam::GetPosition()
{
    return m_Position;
}
