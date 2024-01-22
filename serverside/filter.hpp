#ifndef _FILTER_HPP
#define _FILTER_HPP

#include "irecipientfilter.h"
#include "bitvec.h"
#include "tier1/utlvector.h"
#include "eiface.h"
#include "iface.hpp"
class CRecipientFilter : public IRecipientFilter
{
public:
	CRecipientFilter(void) {};
	CRecipientFilter(int p) {
		this->AddRecipient(p);
	};
	~CRecipientFilter(void) {};

	virtual bool IsReliable(void) const { return false; }
	virtual bool IsInitMessage(void) const { return false; }

	virtual int GetRecipientCount(void) const;
	virtual int GetRecipientIndex(int slot) const;
	void AddAllPlayers();
	void AddRecipient(int iPlayer);

private:
	CUtlVector<int> m_Recipients;
};

int CRecipientFilter::GetRecipientCount() const
{
	return m_Recipients.Size();
}

int CRecipientFilter::GetRecipientIndex(int slot) const
{
	if (slot < 0 || slot >= GetRecipientCount())
		return -1;

	return m_Recipients[slot];
}

void CRecipientFilter::AddAllPlayers()
{
	m_Recipients.RemoveAll();

	for (int i = 1; i <= 16; i++)
	{
		edict_t* pPlayer = engine->PEntityOfEntIndex(i);

		if (!pPlayer || pPlayer->IsFree())
			continue;

		m_Recipients.AddToTail(i);
	}
}
void CRecipientFilter::AddRecipient(int iPlayer)
{
	if (iPlayer == 0) {
		this->AddAllPlayers();
		return;
	}

	if (m_Recipients.Find(iPlayer) != m_Recipients.InvalidIndex())
		return;

	edict_t* pPlayer = engine->PEntityOfEntIndex(iPlayer);
	if (!pPlayer || pPlayer->IsFree())
		return;

	m_Recipients.AddToTail(iPlayer);
}

#endif