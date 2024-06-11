#include "ThreadWorker.hpp"
#include "shared/self_obfuscation/strenc.hpp"

CThread::CThread(std::function<void()> task) : wxThread(wxTHREAD_DETACHED), m_task(task) {}

wxThread::ExitCode CThread::Entry()
{
    m_task();
    return (wxThread::ExitCode)0;
}

CThreadWorker::CThreadWorker(wxEvtHandler* parent) : m_parent(parent) {}

void CThreadWorker::doHeavyLifting(std::function<void()> task)
{
    CThread* thread = new CThread(task);
    if (thread->Run() != wxTHREAD_NO_ERROR)
    {
        wxLogError(strenc("Could not start thread!"));
        delete thread;
    }
}

