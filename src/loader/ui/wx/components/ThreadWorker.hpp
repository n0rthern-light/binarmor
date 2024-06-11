#pragma once

#include <wx/wx.h>
#include <wx/thread.h>
#include <functional>

class CThread : public wxThread
{
    std::function<void()> m_task;
protected:
    virtual wxThread::ExitCode Entry() override;
public:
    CThread(std::function<void()> task);
};

class CThreadWorker : public wxEvtHandler
{
    wxEvtHandler* m_parent;
public:
    CThreadWorker(wxEvtHandler* parent);
    void doHeavyLifting(std::function<void()> task);
};

