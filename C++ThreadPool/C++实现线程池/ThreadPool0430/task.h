#pragma once

#include <vector>
#include <pthread.h>
#include <string>

/**
 * ִ��������� �� �����������ݲ�ִ��
*/
class CTask {
protected:
    std::string m_strTaskName;          /** ��������� */
    void        *m_ptrData;             /** Ҫִ������ľ������� */
public:
    CTask() = default;
    CTask(std::string taskName) {
        m_strTaskName = taskName;
        m_ptrData = nullptr;
    }
    virtual Run() = 0;                  /** �ӿ� */
    void    SetData(void *data);        /** ������������ */
public:
    virtual ~CTask() = default;
};
