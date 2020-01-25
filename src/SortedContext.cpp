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
	    if(m_contextStack.size()>1)
		m_contextStack.erase(name);
	    else
		m_contextStack.clear();
	    for(auto it = m_sortedContexts.begin(); it != m_sortedContexts.end(); ++it)
	    {
		if((*it).first == ctx)
		{
		    if(m_sortedContexts.size()>1)
			m_sortedContexts.erase(it);
		    else
			m_sortedContexts.clear();
		}
	    }
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
