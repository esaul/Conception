#pragma once
#ifndef __Pointer_H__
#define __Pointer_H__

class Pointer
	: public InputHandler,
	  public MutuallyConnectable<Pointer, GestureRecognizer>
{
public:
	enum class DeviceCategory : uint8 { KEYBOARD, MOUSE, TOUCH };
	enum class VirtualCategory : uint8 { TYPING, POINTING };

	void ProcessEvent(InputEvent & InputEvent) override;

	void ProcessTimePassed(const double TimePassed) override;

	virtual DeviceCategory GetDeviceCategory() const = 0;
	virtual VirtualCategory GetVirtualCategory() const = 0;

	const PointerMapping & GetPointerMapping();
	PointerMapping & ModifyPointerMapping();

	const PointerState & GetPointerState();
	PointerState & ModifyPointerState();

protected:
	Pointer(InputHandler & InputHandler);
	virtual ~Pointer();

	void ProcessActivation(InputEvent & InputEvent);
	void ProcessDeactivation(InputEvent & InputEvent);

private:
	Pointer(const Pointer &) = delete;
	Pointer & operator = (const Pointer &) = delete;

	PointerState		m_PointerState;

	InputHandler &		m_InputHandler;
	PointerMapping		m_PointerMapping;
public:PointerMapping		m_CurrentPointerMappingTEST;private:		// HACK: Competes with regular GetPointerMapping(), but represents _now_ state, regardless of pointer being active
																		// TODO: Should probably merge this into GetPointerMapping(), but clone GetPointerMapping() into GetEventTargetPointerMapping() which is where events go (i.e. at pointer activation)
};

#endif // __Pointer_H__
