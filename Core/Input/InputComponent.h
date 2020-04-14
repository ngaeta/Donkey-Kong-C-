#ifndef AIV_INPUT_COMPONENT
#define AIV_INPUT_COMPONENT

namespace DonkeyKong
{
	class GameObject;

	class InputComponent
	{
	public:
		virtual ~InputComponent() = default;
		virtual void Update(GameObject&) = 0;
	};
}

#endif
