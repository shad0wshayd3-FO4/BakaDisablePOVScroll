namespace Hooks
{
	namespace hkFirstPersonState
	{
		static void Install()
		{
			static REL::Relocation target{ REL::ID(2248265) };
			static constexpr auto  TARGET_ADDR{ 0x54 };
			static constexpr auto  TARGET_RETN{ 0xB8 };
			static constexpr auto  TARGET_FILL{ TARGET_RETN - TARGET_ADDR };
			target.write_fill<TARGET_ADDR>(REL::NOP, TARGET_FILL);
		}
	}

	namespace hkThirdPersonState
	{
		static void Install()
		{
			static REL::Relocation target{ REL::ID(2248467) };
			static constexpr auto  TARGET_ADDR{ 0x203 };
			static constexpr auto  TARGET_RETN{ 0x26E };
			static constexpr auto  TARGET_FILL{ TARGET_RETN - TARGET_ADDR };
			target.write_fill<TARGET_ADDR>(REL::NOP, TARGET_FILL);
		}
	}

	static void Install()
	{
		hkFirstPersonState::Install();
		hkThirdPersonState::Install();
	}
}

namespace
{
	void MessageCallback(F4SE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type)
		{
		case F4SE::MessagingInterface::kPostLoad:
			Hooks::Install();
			break;
		default:
			break;
		}
	}
}

F4SE_PLUGIN_LOAD(const F4SE::LoadInterface* a_f4se)
{
	F4SE::Init(a_f4se);
	F4SE::GetMessagingInterface()->RegisterListener(MessageCallback);
	return true;
}
