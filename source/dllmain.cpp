#include <misc.h>

uint32_t* dword_11CC9D0;
int32_t* dword_112EAC0;
int32_t* dword_11402D4;
int32_t* dword_F30468;
float* float_F33C18;
LARGE_INTEGER(*sub_456F60)();
int64_t* qword_11CCA80;
float* float_18CAE9C;
void* unk_11CC9D8;
double* qword_10FCB84;
float* float_F33C24;
float* float_11CC9D4;
void(__cdecl* sub_855470)(float a1);
bool(*CCutscenes__hasCutsceneFinished)();
bool(*CCamera__isWidescreenBordersActive)();

int32_t nFrameLimitType;
float fFpsLimit;
float fCutsceneFpsLimit;
float fScriptCutsceneFpsLimit;
float fScriptCutsceneFovLimit;

void __cdecl sub_855640()
{
    //injector::fastcall<void(uintptr_t)>::call(*(uintptr_t*)(*(uintptr_t*)(*dword_11CC9D0) + 20), *dword_11CC9D0);

    static auto wants_to_limit_fps = []() -> bool
    {
        if (fFpsLimit)
            return true;

        if (CCamera__isWidescreenBordersActive())
        {
            if (CCutscenes__hasCutsceneFinished())
            {
                if (fCutsceneFpsLimit)
                    return true;
            }
            else if (fScriptCutsceneFpsLimit)
                return true;
        }

        return false;
    };

    static auto get_fps_limit = []() -> float
    {
        float limit = 30.0f;

        if (fFpsLimit)
            limit = fFpsLimit;

        if (CCamera__isWidescreenBordersActive())
        {
            if (CCutscenes__hasCutsceneFinished())
            {
                if (fCutsceneFpsLimit)
                    limit = fCutsceneFpsLimit;
            }
            else if (fScriptCutsceneFpsLimit)
                limit = fScriptCutsceneFpsLimit;
        }

        return limit;
    };

    if (wants_to_limit_fps() || *dword_112EAC0 == 1 || *dword_11402D4 != -1 || *dword_F30468 == 18)
    {
        if (nFrameLimitType == 0)
        {
            *float_F33C18 = 2.0f;
            if (*dword_112EAC0 == 1 || *dword_11402D4 != -1 || *dword_F30468 == 18)
                *float_F33C18 = 1.0f;
            double v1 = (double)((*float_F33C18 - 0.1f) * ((1.0f / get_fps_limit()) / 2.0f));
            double v3 = (double)(sub_456F60().QuadPart - *qword_11CCA80);
            if (v1 > v3 * *float_18CAE9C)
            {
                do
                {
                    v3 = (double)(sub_456F60().QuadPart - *qword_11CCA80) * *float_18CAE9C;
                    Sleep(0);
                }
                while (v1 > v3);
            }
            *qword_11CCA80 = sub_456F60().QuadPart;
        }
        else
        {
            static LARGE_INTEGER PerformanceCount1;
            static LARGE_INTEGER PerformanceCount2;
            static bool bOnce1 = false;
            static double t = 0.0;
            static DWORD i = 0;
            double targetFrameTime = 1000.0 / get_fps_limit();

            if (!bOnce1)
            {
                bOnce1 = true;
                QueryPerformanceCounter(&PerformanceCount1);
                PerformanceCount1.QuadPart = PerformanceCount1.QuadPart >> i;
            }

            while (true)
            {
                QueryPerformanceCounter(&PerformanceCount2);
                if (t == 0.0)
                {
                    LARGE_INTEGER PerformanceCount3;
                    static bool bOnce2 = false;

                    if (!bOnce2)
                    {
                        bOnce2 = true;
                        QueryPerformanceFrequency(&PerformanceCount3);
                        i = 0;
                        t = 1000.0 / (double)PerformanceCount3.QuadPart;
                        auto v = t * 2147483648.0;
                        if (60000.0 > v)
                        {
                            while (true)
                            {
                                ++i;
                                v *= 2.0;
                                t *= 2.0;
                                if (60000.0 <= v)
                                    break;
                            }
                        }
                    }
                    SleepEx(0, 1);
                    break;
                }

                if (((double)((PerformanceCount2.QuadPart >> i) - PerformanceCount1.QuadPart) * t) >= targetFrameTime)
                    break;

                SleepEx(0, 1);
            }
            QueryPerformanceCounter(&PerformanceCount2);
            PerformanceCount1.QuadPart = PerformanceCount2.QuadPart >> i;
        }
    }

    //is that even used?
    {
        auto v2 = 0.0f;
        auto v01 = (uint8_t **)unk_11CC9D8;
        auto v02 = v01[2];
        if (v02 && *v02)
            v2 = atof((const char*)v01[2]);

        if (v2 > 0.0f)
        {
            auto v0 = *qword_10FCB84;
            if (*qword_10FCB84 < 0.0083333002f)
                v0 = 0.0083333002f;
            *float_F33C24 = (((60.0f - 1.0f) * (1.0f / 60.0f)) * *float_F33C24) + ((1.0f / v0) * (1.0f / 60.0f));
            if ((v2 - 3.0f) <= *float_F33C24)
            {
                if (*float_F33C24 > (v2 + 3.0f))
                {
                    sub_855470(1.0 + 0.029999999f);
                    *float_11CC9D4 = 1.0f;
                }
            }
            else
            {
                sub_855470(1.0f - 0.029999999f);
                *float_11CC9D4 = -1.0f;
            }
        }
    }
}

uint32_t dword_F43AD8;
uint32_t dword_1826D48;
uint32_t dword_1826D34;
uint32_t dword_1826D4C;
uint32_t dword_1826D6C;
double __cdecl MouseFix(void*, int32_t axis)
{
    auto address = *(int32_t*)(dword_F43AD8 + 0xC);
    if (*(BYTE*)(address + 0x1C4) & 8)
    {
        *(int32_t*)(dword_1826D48) = 0;
        *(int32_t*)(dword_1826D34) = 0;
        *(int32_t*)(dword_1826D4C) = 0;
        *(int32_t*)(dword_1826D6C) = 0;
    }
    if (axis == 0)
    {
        return (double)(*(int32_t*)(dword_1826D48)) * 0.0078125;
    }
    else if (axis == 1)
    {
        return (double)(*(int32_t*)(dword_1826D34)) * 0.0078125;
    }

    return 0.0;
}

void Init()
{
    CIniReader iniReader("");
    //[MAIN]
    bool bRecoilFix = iniReader.ReadInteger("MAIN", "RecoilFix", 1) != 0;
    bool bDefinitionFix = iniReader.ReadInteger("MAIN", "DefinitionFix", 1) != 0;
    bool bEmissiveShaderFix = iniReader.ReadInteger("MAIN", "EmissiveShaderFix", 1) != 0;
    bool bHandbrakeCamFix = iniReader.ReadInteger("MAIN", "HandbrakeCamFix", 1) != 0;
    int32_t nAimingZoomFix = iniReader.ReadInteger("MAIN", "AimingZoomFix", 1);
    bool bFlickeringShadowsFix = iniReader.ReadInteger("MAIN", "FlickeringShadowsFix", 1) != 0;

    //[FRAMELIMIT]
    nFrameLimitType = iniReader.ReadInteger("FRAMELIMIT", "FrameLimitType", 1);
    fFpsLimit = static_cast<float>(iniReader.ReadInteger("FRAMELIMIT", "FpsLimit", 0));
    fCutsceneFpsLimit = static_cast<float>(iniReader.ReadInteger("FRAMELIMIT", "CutsceneFpsLimit", 0));
    fScriptCutsceneFpsLimit = static_cast<float>(iniReader.ReadInteger("FRAMELIMIT", "ScriptCutsceneFpsLimit", 0));
    fScriptCutsceneFovLimit = static_cast<float>(iniReader.ReadInteger("FRAMELIMIT", "ScriptCutsceneFovLimit", 0));

    //[MISC]
    bool bDefaultCameraAngleInTLAD = iniReader.ReadInteger("MISC", "DefaultCameraAngleInTLAD", 0) != 0;
    bool bPedDeathAnimFixFromTBOGT = iniReader.ReadInteger("MISC", "PedDeathAnimFixFromTBOGT", 1) != 0;
    bool bDisableCameraCenteringInCover = iniReader.ReadInteger("MISC", "DisableCameraCenteringInCover", 1) != 0;
    bool bMouseFix = iniReader.ReadInteger("MISC", "MouseFix", 0) != 0;

    static float& fTimeStep = **hook::get_pattern<float*>("D8 0D ? ? ? ? 83 C0 30", -9);

    // animation fix for phone interaction on bikes
    {
        auto pattern = hook::pattern("83 3D ? ? ? ? 01 0F 8C 1C 01 00 00");
        injector::MakeNOP(pattern.get(0).get<int>(0), 13, true);
    }

    //fix for lods appearing inside normal models, unless the graphics menu was opened once (draw distances aren't set properly?)
    {
        auto pattern = hook::pattern("E8 ? ? ? ? 8D 44 24 10 83 C4 04");
        auto sub_477300 = injector::GetBranchDestination(pattern.get_first(0));
        pattern = hook::pattern("E8 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? 8B 35 ? ? ? ? E8 ? ? ? ? 25 ? ? ? ? 89 44 24 0C DB");
        injector::MakeCALL(pattern.get_first(0), sub_477300, true);
    }

    //fix for zoom flag in tbogt
    if (nAimingZoomFix)
    {
        auto pattern = hook::pattern("8A D0 32 15");
        static auto& byte_F47AB1 = **pattern.get_first<uint8_t*>(4);
        if (nAimingZoomFix > 1)
            injector::MakeNOP(pattern.get_first(-2), 2, true);
        else if (nAimingZoomFix < 0)
            injector::WriteMemory<uint8_t>(pattern.get_first(-2), 0xEB, true);

        pattern = hook::pattern("08 9E ? ? ? ? E9");
        struct AimZoomHook1
        {
            void operator()(injector::reg_pack& regs)
            {
                *(uint8_t*)(regs.esi + 0x200) |= 1;
                byte_F47AB1 = 1;
            }
        }; injector::MakeInline<AimZoomHook1>(pattern.get_first(0), pattern.get_first(6));

        pattern = hook::pattern("80 A6 ? ? ? ? ? EB 25");
        struct AimZoomHook2
        {
            void operator()(injector::reg_pack& regs)
            {
                *(uint8_t*)(regs.esi + 0x200) &= 0xFE;
                byte_F47AB1 = 0;
            }
        }; injector::MakeInline<AimZoomHook2>(pattern.get_first(0), pattern.get_first(7));

        //let's default to 0 as well
        pattern = hook::pattern("88 1D ? ? ? ? 74 10");
        injector::WriteMemory<uint8_t>(pattern.get_first(1), 0x25, true); //mov ah
    }

    if (bFlickeringShadowsFix)
    {
        auto pattern = hook::pattern("52 8D 44 24 50 50 68");
        injector::WriteMemory(pattern.get_first(7), 0x100, true);
    }

    if (bRecoilFix)
    {
        static float fRecMult = 0.65f;
        auto pattern = hook::pattern("F3 0F 10 44 24 ? F3 0F 59 05 ? ? ? ? EB ? E8");
        injector::WriteMemory(pattern.get_first(10), &fRecMult, true);
    }

    if (bDefinitionFix)
    {
        //disable forced definition-off in cutscenes
        auto pattern = hook::pattern("E8 ? ? ? ? F6 D8 1A C0 F6 D0 22 05 ? ? ? ? C3"); //0x88CC6B
        injector::WriteMemory<uint16_t>(pattern.get_first(11), 0xA090, true); //mov al ...
    }

    if (bEmissiveShaderFix)
    {
        // workaround for gta_emissivestrong.fxc lights on patch 6+,
        //"A0 01 00 00 02 00 00 08" replaced in shader files with "A1 01 00 00 02 00 00 08" (5 occurrences)
        auto pattern = hook::pattern("C1 E7 04 C1 E3 04 8B C7 83 F8 04 8D 9B ? ? ? ? 8B CB 72 14 8B 32 3B 31 75 12 83 E8 04");
        struct ShaderTest
        {
            void operator()(injector::reg_pack& regs)
            {
                if (
                    *(uint32_t*)(regs.edx + 0x00) == 0x39D1B717 &&
                    *(uint32_t*)(regs.edx + 0x10) == 0x41000000 && //traffic lights and lamps
                    *(uint32_t*)(regs.edx - 0x10) == 0x3B03126F &&
                    *(uint32_t*)(regs.edx + 0x20) == 0x3E59999A &&
                    *(uint32_t*)(regs.edx + 0x24) == 0x3F372474 &&
                    *(uint32_t*)(regs.edx + 0x28) == 0x3D93A92A
                )
                {
                    auto f_ptr = (uint32_t*)(regs.edx - 0x158);
                    if (f_ptr)
                    {
                        //auto f_00 = f_ptr[3];
                        //auto f_01 = f_ptr[7];
                        auto f_02 = f_ptr[18];
                        auto f_04 = f_ptr[10];
                        auto f_05 = f_ptr[13];
                        //auto f_06 = f_ptr[12];
                        //auto f_07 = f_ptr[17];
                        auto f_08 = f_ptr[19];
                        //auto f_09 = f_ptr[22];
                        //auto f_10 = f_ptr[23];
                        //auto f_11 = f_ptr[24];

                        if ((f_05 != 0x7f800001 && f_05 != 0xcdcdcdcd && f_04 == 0x00000000 && f_08 != 0xba8bfc22 && f_02 != 0x3f800000)
                                || (f_02 == 0x3f800000 && f_04 == 0x42480000 && f_05 == 0x00000000 && f_08 == 0x00000000))
                        {
                            *(float*)(regs.edx + 0x00) = -*(float*)(regs.edx + 0x00);
                        }
                    }
                }

                regs.edi = regs.edi << 4;
                regs.ebx = regs.ebx << 4;
            }
        }; injector::MakeInline<ShaderTest>(pattern.count(2).get(1).get<void>(0), pattern.count(2).get(1).get<void>(6)); //417800

        //pattern = hook::pattern("0F B6 29 0F B6 32 2B F5 75 45 83 E8 01 83 C1 01 83 C2 01 85 C0");
        //struct ShaderTest2
        //{
        //    void operator()(injector::reg_pack& regs)
        //    {
        //        *(uint8_t*)&regs.ebp = *(uint8_t*)(regs.ecx + 0x00);
        //        *(uint8_t*)&regs.esi = *(uint8_t*)(regs.edx + 0x00);
        //    }
        //}; injector::MakeInline<ShaderTest2>(pattern.count(6).get(3).get<void>(0), pattern.count(6).get(3).get<void>(6)); //41782D

        //BAWSAQ
        pattern = hook::pattern("E8 ? ? ? ? 6A 00 E8 ? ? ? ? 83 C4 14 6A 00 B9 ? ? ? ? E8 ? ? ? ? 39 35 ? ? ? ? 75 09 6A 01");
        static auto CImgManager__addImgFile = (void(__cdecl*)(const char*, char, int)) injector::GetBranchDestination(pattern.get_first(0)).get();
        static auto sub_A95980 = (void(__cdecl*)(char)) injector::GetBranchDestination(pattern.get_first(7)).get();

        pattern = hook::pattern("B9 ? ? ? ? E8 ? ? ? ? 84 C0 74 22 68");
        static auto g_assetManager = *pattern.get_first<uint32_t>(1);
        struct AddImgHook
        {
            void operator()(injector::reg_pack& regs)
            {
                regs.ecx = g_assetManager;

                sub_A95980(255);
                CImgManager__addImgFile("common:/GTAIV.EFLC.FusionFix.img", 1, -1);
                sub_A95980(0);
            }
        }; injector::MakeInline<AddImgHook>(pattern.get_first(0));
    }

    if (bHandbrakeCamFix)
    {
        auto pattern = hook::pattern("D9 44 24 20 8B 54 24 64 F3 0F 10 02 51 D9 1C 24 8D 44 24 20 50");
        struct HandbrakeCam
        {
            void operator()(injector::reg_pack& regs)
            {
                *(float*)(regs.esp + 0x20) *= (1.0f / 30.0f) / fTimeStep;
                float f = *(float*)(regs.esp + 0x20);
                regs.edx = *(uint32_t*)(regs.esp + 0x64);
                _asm fld dword ptr[f]
            }
        }; injector::MakeInline<HandbrakeCam>(pattern.get_first(0), pattern.get_first(8));
    }

    //camera position in TLAD
    if (bDefaultCameraAngleInTLAD)
    {
        static uint32_t episode_id = 0;
        auto pattern = hook::pattern("83 3D ? ? ? ? ? 75 06 C7 00 ? ? ? ? B0 01 C2 08 00");
        injector::WriteMemory(pattern.count(2).get(0).get<void>(2), &episode_id, true);
    }

    if (bPedDeathAnimFixFromTBOGT)
    {
        auto pattern = hook::pattern("BB ? ? ? ? 75 29");
        injector::MakeNOP(pattern.get_first(5), 2, true);
    }

    if (bDisableCameraCenteringInCover)
    {
        static constexpr float xmm_0 = FLT_MAX / 2.0f;
        auto pattern = hook::pattern("F3 0F 10 05 ? ? ? ? F3 0F 58 46 ? 89 8C 24");
        injector::WriteMemory(pattern.get_first(4), &xmm_0, true);
    }

    if (bMouseFix)
    {
        auto pattern = hook::pattern("B9 ? ? ? ? E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? 80 7D 08 00");
        dword_F43AD8 = *pattern.get_first<uint32_t>(1);
        pattern = hook::pattern("53 33 DB 38 5C 24 08 74 26");
        dword_1826D48 = *pattern.get_first<int32_t>(11);
        dword_1826D34 = *pattern.get_first<int32_t>(11+6);
        dword_1826D4C = *pattern.get_first<int32_t>(11+6+6);
        dword_1826D6C = *pattern.get_first<int32_t>(11+6+6+6);
        pattern = hook::pattern("51 8B 44 24 0C 85 C0 0F 57 D2 56 8B 35");
        injector::MakeJMP(pattern.get_first(0), MouseFix, true);
    }

    if (fFpsLimit || fCutsceneFpsLimit || fScriptCutsceneFpsLimit)
    {
        //auto pattern = hook::pattern("6A 01 51 8B CE D9 1C 24 E8 ? ? ? ? D9 54 24 2C D9 EE 8A 44 24 1B D9 C9 DF F1 DD D8 76 18");
        //injector::WriteMemory<uint8_t>(pattern.get_first(1), 0, true); //intro cutscene fix?

        dword_11CC9D0 = *hook::get_pattern<uint32_t*>("8B 0D ? ? ? ? 8B 01 8B 50 14 83 EC 18", 2);
        float_11CC9D4 = (float*)(dword_11CC9D0 + 1);
        unk_11CC9D8 = dword_11CC9D0 + 2;
        dword_112EAC0 = *hook::get_pattern<int32_t*>("D9 5C 24 0C A1", 5);
        dword_11402D4 = *hook::get_pattern<int32_t*>("A3 ? ? ? ? E8 ? ? ? ? 83 C4 08 C7 05", 1);
        dword_F30468 = *hook::get_pattern<int32_t*>("A1 ? ? ? ? 74 0E 83 3D", 1);
        float_F33C18 = *hook::get_pattern<float*>("D9 05 ? ? ? ? D8 25 ? ? ? ? D8 0D", 2);
        float_F33C24 = *hook::get_pattern<float*>("F3 0F 59 05 ? ? ? ? 0F 28 EA F3 0F 5E EB", 4);
        qword_11CCA80 = *hook::get_pattern<int64_t*>("A3 ? ? ? ? 89 15 ? ? ? ? 0F 57 C0", 1);
        float_18CAE9C = *hook::get_pattern<float*>("89 75 E4 F3 0F 10 05", 7);
        qword_10FCB84 = *hook::get_pattern<double*>("D9 05 ? ? ? ? 53 D8 0D ? ? ? ? 56 D9 7C 24 0C", 2);
        sub_456F60 = (LARGE_INTEGER(*)()) hook::get_pattern<void*>("55 8B EC 83 E4 F8 83 EC 18 53 55 56 33 F6 39 35", 0);
        sub_855470 = (void(*)(float)) hook::get_pattern<void*>("F3 0F 10 05 ? ? ? ? F3 0F 59 44 24 ? F3 0F 10 0D ? ? ? ? F3 0F 2A 15", 0);

        auto pattern = hook::pattern("E8 ? ? ? ? 84 C0 75 89");
        CCutscenes__hasCutsceneFinished = (bool(*)()) injector::GetBranchDestination(pattern.get_first(0)).get();
        pattern = hook::pattern("E8 ? ? ? ? 84 C0 75 42 38 05");
        CCamera__isWidescreenBordersActive = (bool(*)()) injector::GetBranchDestination(pattern.get_first(0)).get();

        //pattern = hook::pattern("6A 01 55 E8 ? ? ? ? 83 C4 08 E8 ? ? ? ? 5F 5E 5D 5B 8B E5 5D C3");
        //injector::MakeCALL(pattern.get_first(11), sub_855640, true);
        //pattern = hook::pattern("89 48 24 E8 ? ? ? ? E8 ? ? ? ? 8B 8C 24 ? ? ? ? 5F 5E 33 CC E8 ? ? ? ? 81 C4 ? ? ? ? C3");
        //injector::MakeCALL(pattern.get_first(8), sub_855640, true);
        //pattern = hook::pattern("C7 40 ? ? ? ? ? EB 02 33 C0 8B C8 E8 ? ? ? ? 6A 00 6A 08 E8 ? ? ? ? 83 C4 08 85 C0 74 0E 8B C8 E8");
        //injector::WriteMemory(pattern.get_first(3), sub_855640, true);
        pattern = hook::pattern("A1 ? ? ? ? 83 F8 01 8B 0D ? ? ? ? 8B 15 ? ? ? ? 8B 35 ? ? ? ? 74 0D 3B CA");
        injector::WriteMemory(pattern.get_first(0), 0x901CC483, true);
        injector::MakeJMP(pattern.get_first(4), sub_855640, true);
    }

    if (fScriptCutsceneFovLimit)
    {
        auto pattern = hook::pattern("D9 46 0C D9 58 60 5E C3");
        struct SetFOVHook
        {
            void operator()(injector::reg_pack& regs)
            {
                float f = *(float*)(regs.esi + 0x0C);
                *(float*)(regs.eax + 0x60) = f > fScriptCutsceneFovLimit ? f : fScriptCutsceneFovLimit;
            }
        }; injector::MakeInline<SetFOVHook>(pattern.get_first(0), pattern.get_first(6));
    }
}

CEXP void InitializeASI()
{
    std::call_once(CallbackHandler::flag, []()
    {
        CallbackHandler::RegisterCallback(Init, hook::pattern("F3 0F 10 44 24 ? F3 0F 59 05 ? ? ? ? EB ? E8"));
    });
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        if (!IsUALPresent()) { InitializeASI(); }
    }
    return TRUE;
}