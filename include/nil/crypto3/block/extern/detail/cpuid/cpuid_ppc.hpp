#include <nil/crypto3/utilities/cpuid/cpuid.hpp>
#include <nil/crypto3/utilities/os_utils.hpp>

#if defined(BOOST_ARCH_PPC)

/*
 * On Darwin and OpenBSD ppc, use sysctl to detect AltiVec
 */
#if defined(CRYPTO3_TARGET_OS_IS_DARWIN)
#include <sys/sysctl.h>
#elif defined(CRYPTO3_TARGET_OS_IS_OPENBSD)
#include <sys/param.h>
#include <sys/sysctl.h>
#include <machine/cpu.h>
#elif defined(CRYPTO3_TARGET_OS_HAS_GETAUXVAL)
#include <sys/auxv.h>
#endif

#endif

namespace nil {
    namespace crypto3 {

#if defined(BOOST_ARCH_PPC)

        /*
         * PowerPC specific block: check for AltiVec using either
         * sysctl or by reading processor version number register.
         */
        uint64_t cpuid::detect_cpu_features(size_t *cache_line_size) {
            CRYPTO3_UNUSED(cache_line_size);

#if defined(CRYPTO3_TARGET_OS_IS_DARWIN) || defined(CRYPTO3_TARGET_OS_IS_OPENBSD)
            // On Darwin/OS X and OpenBSD, use sysctl

            int sels[2] = {
#if defined(CRYPTO3_TARGET_OS_IS_OPENBSD)
                CTL_MACHDEP,
                CPU_ALTIVEC
#else
                CTL_HW,
                HW_VECTORUNIT
#endif
            };

            int vector_type = 0;
            size_t length = sizeof(vector_type);
            int error = ::sysctl(sels, 2, &vector_type, &length, NULL, 0);

            if (error == 0 && vector_type > 0)
                return cpuid::CPUID_ALTIVEC_BIT;

#elif defined(CRYPTO3_TARGET_OS_HAS_GETAUXVAL) && defined(CRYPTO3_TARGET_ARCHITECTURE_IS_PPC64)

            enum PPC_hwcap_bit {
                ALTIVEC_bit = (1 << 28),
                CRYPTO3_bit = (1 << 25),

                ARCH_hwcap_altivec = 16,    // AT_HWCAP
                ARCH_hwcap_crypto = 26,     // AT_HWCAP2
            };

            uint64_t detected_features = 0;

            const unsigned long hwcap_altivec = ::getauxval(PPC_hwcap_bit::ARCH_hwcap_altivec);
            if (hwcap_altivec & PPC_hwcap_bit::ALTIVEC_bit)
                detected_features |= cpuid::CPUID_ALTIVEC_BIT;

            const unsigned long hwcap_crypto = ::getauxval(PPC_hwcap_bit::ARCH_hwcap_crypto);
            if (hwcap_crypto & PPC_hwcap_bit::CRYPTO3_bit)
                detected_features |= cpuid::CPUID_PPC_CRYPTO3_BIT;

            return detected_features;

#else

            /*
            On PowerPC, MSR 287 is PVR, the Processor Version Number
            Normally it is only accessible to ring 0, but Linux and NetBSD
            (others, too, maybe?) will trap and emulate it for us.
            */

            int pvr = run_cpu_instruction_probe([]() -> int {
                uint32_t pvr = 0;
                asm volatile("mfspr %0, 287" : "=r"(pvr));
                // Top 16 bits suffice to identify the model
                return static_cast<int>(pvr >> 16);
            });

            if (pvr > 0) {
                const uint16_t ALTIVEC_PVR[] = {
                    0x003E,    // IBM POWER6
                    0x003F,    // IBM POWER7
                    0x004A,    // IBM POWER7p
                    0x004D,    // IBM POWER8
                    0x004B,    // IBM POWER8E
                    0x000C,    // G4-7400
                    0x0039,    // G5 970
                    0x003C,    // G5 970FX
                    0x0044,    // G5 970MP
                    0x0070,    // Cell PPU
                    0,         // end
                };

                for (size_t i = 0; ALTIVEC_PVR[i]; ++i) {
                    if (pvr == ALTIVEC_PVR[i])
                        return cpuid::CPUID_ALTIVEC_BIT;
                }

                return 0;
            }

            // TODO try direct instruction probing

#endif

            return 0;
        }

#endif
    }    // namespace crypto3
}    // namespace nil
