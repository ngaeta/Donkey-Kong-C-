#ifndef AIV_ENV
#define AIV_ENV

namespace DonkeyKong
{
	class Env final
	{
	public:
		Env();
		~Env();

		explicit operator bool();

	private:
		bool init;
	};
}

#endif
