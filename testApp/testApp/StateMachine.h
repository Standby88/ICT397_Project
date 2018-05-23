#ifndef STATEMACHINE_H
#define STATEMACHINE_H

template <class entity_type>

class StateMachine
{
private:
	entity_type * m_pOwner;

	State<entity_type>* m_pCurrentState;

	State<entity_type>* m_pPreviousState;

	State<entity_type>* m_pGlobalState;

public:
	StateMachine(entity_type * owner) : m_pOwner(owner),
		m_pCurrentState(NULL),
		m_pPreviousState(NULL),
		m_pGlobalState(NULL)
	{}

	void SetCurrentState(State<entity_type> * s)
	{
		m_pCurrentState = s;
	}

	void SetGlobalState(State<entity_type> * s)
	{
		m_pGlobalState = s;
	}

	void SetPreviousState(State<entity_type> * s)
	{
		m_pPreviousState = s;
	}

	void Update()const
	{
		if (m_pGlobalState)
			m_pGlobalState->Execute(m_pOwner);

		if (m_pCurrentState)
			m_pCurrentState->Execute(m_pOwner);
	}

	void ChangeState(State<entity_type> * NewState)
	{
		asset(NewState && "<StateMachine::ChangeState>: trying to change to a null state");

		m_pPreviousState = m_pCurrentState;

		m_pCurrentState->Exit(m_pOwner);

		m_pCurrentState = NewState;

		m_pCurrentState->Enter(m_pOwner);
	}

	void RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	// useful accessors
	State<entity_type>* CurrentState() const
	{
		return m_pCurrentState;
	}

	State<entity_type>* GlobalState() const
	{
		return m_pGlobalState;
	}

	State<entity_type>* PrevioustState() const
	{
		return m_pPreviousState;
	}

	bool IsInState(const State<entity_type> & st) const;
};

#endif