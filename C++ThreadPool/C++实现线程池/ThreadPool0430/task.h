#pragma once

#include <vector>
#include <pthread.h>
#include <string>

/**
 * 执行任务的类 ： 设置任务数据并执行
*/
class CTask {
protected:
    std::string m_strTaskName;          /** 任务的名称 */
    void        *m_ptrData;             /** 要执行任务的具体数据 */
public:
    CTask() = default;
    CTask(std::string taskName) {
        m_strTaskName = taskName;
        m_ptrData = nullptr;
    }
    virtual Run() = 0;                  /** 接口 */
    void    SetData(void *data);        /** 设置任务数据 */
public:
    virtual ~CTask() = default;
};
