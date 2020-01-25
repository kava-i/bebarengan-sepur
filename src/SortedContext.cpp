#include "SortedContext.hpp"

CContextStack::CContextStack()
{
    m_reloadQueue = false;
}

void CContextStack::insert(CContext *ctx, int priority, std::string name)
{
    m_contextStack[name] = ctx;
    m_sortedContexts.push_back(std::pair<CContext*,int>{ctx,priority});
    std::sort(m_sortedContexts.begin(),m_sortedContexts.end(),[](std::pair<CContext*,int>& a,std::pair<CContext*,int>& b){return a.second<b.second;});
    m_reloadQueue = true;
}

void CContextStack::erase(std::string name)
{
    CContext* ctx = nullptr;
    try
    {
	ctx = m_contextStack.at(name);
	m_reloadQueue = true;
	m_contextStack.erase(name);
	m_sortedContexts.erase(std::remove_if(m_sortedContexts.begin(),m_sortedContexts.end(),[ctx](const std::pair<CContext*,int> &p){if(p.first==ctx)return true; else return false;}),m_sortedContexts.end());
    }
    catch(...)
    {
	return;
    }
}

const std::deque<CContext*> &CContextStack::getSortedCtxList()
{
    if(m_reloadQueue)
    {
	m_sortedQueue.clear();
	for(auto &it : m_sortedContexts)
	    m_sortedQueue.push_front(it.first);
	m_reloadQueue = false;
    }
    return m_sortedQueue;
}
