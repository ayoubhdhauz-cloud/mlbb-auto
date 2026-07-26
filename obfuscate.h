#ifndef KABRAXHIDE_H
#define KABRAXHIDE_H

#include <cstdint>
#include <cstddef>

#ifdef __OBJC__
    #import <Foundation/Foundation.h>
    #import <objc/runtime.h>
#endif

#if defined(__clang__) || defined(__GNUC__)
    #define KH_INLINE       inline __attribute__((always_inline))
    #define KH_NOINLINE     __attribute__((noinline))
    #define KH_HIDDEN       __attribute__((visibility("hidden")))
#else
    #define KH_INLINE       inline
    #define KH_NOINLINE
    #define KH_HIDDEN
#endif

namespace _kh_ {

    static constexpr uint64_t _seed() {
        return ((__TIME__[0]-'0')*36000ULL) + ((__TIME__[1]-'0')*3600ULL) +
               ((__TIME__[3]-'0')*600ULL)   + ((__TIME__[4]-'0')*60ULL) +
               ((__TIME__[6]-'0')*10ULL)    + (__TIME__[7]-'0');
    }
    static constexpr uint64_t KH_SEED = _seed();

    constexpr uint64_t _lcg(uint64_t x) {
        return (1013904223ULL + 1664525ULL * x) & 0xFFFFFFFFFFFFFFFFULL;
    }
    constexpr uint64_t _mix(uint64_t a, uint64_t b) {
        return _lcg(_lcg(a ^ b) ^ _lcg(b * 2654435769ULL));
    }

    template <uint32_t C, uint32_t L>
    struct KeyGen {
        static constexpr uint64_t m0 = _mix(KH_SEED, (uint64_t)C * 0x9E3779B97F4A7C15ULL);
        static constexpr uint64_t m1 = _mix(m0,      (uint64_t)L * 0xBF58476D1CE4E5B9ULL);
        static constexpr uint64_t m2 = _mix(m1,      (uint64_t)(C ^ L) * 0x94D049BB133111EBULL);
        static constexpr uint64_t m3 = _mix(m2,      m0 ^ m1);
        static constexpr uint64_t m4 = _mix(m3,      m1 ^ m2);
        static constexpr uint8_t key_xor  = static_cast<uint8_t>(m0 & 0xFF);
        static constexpr uint8_t key_add  = static_cast<uint8_t>((m1 >> 8) & 0xFF);
        static constexpr uint8_t key_rot  = static_cast<uint8_t>((m2 >> 16) & 0x07);
        static constexpr uint8_t key_sub  = static_cast<uint8_t>((m3 >> 24) & 0xFF);
        static constexpr uint8_t key_aux1 = static_cast<uint8_t>((m4 >> 8)  & 0xFF);
        static constexpr uint8_t key_aux2 = static_cast<uint8_t>((m4 >> 16) & 0xFF);
        static constexpr int FLAVOR = static_cast<int>(C % 4);
    };

    constexpr uint8_t sbox[256] = {
        0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
        0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
        0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
        0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
        0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
        0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
        0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
        0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
        0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
        0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
        0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
        0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
        0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
        0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
        0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
        0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
    };
    constexpr uint8_t inv_sbox[256] = {
        0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
        0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
        0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
        0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
        0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
        0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
        0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
        0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
        0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
        0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
        0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
        0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
        0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
        0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
        0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
        0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d
    };

    // These keep the compiler from optimizing away our branches
    inline volatile uint32_t _vol_a = 0x9E3779B9;
    inline volatile uint32_t _vol_b = 0x6A09E667;
    inline volatile uint32_t _vol_c = 0xBB67AE85;
    inline volatile uint32_t _vol_d = 0x3C6EF372;
    inline volatile uint32_t _vol_e = 0xA54FF53A;
    inline volatile uint32_t _vol_f = 0x510E527F;

    KH_INLINE constexpr uint8_t enc_flavor_0(uint8_t b, uint8_t kx, uint8_t ka,
                                              uint8_t kr, uint8_t ks, size_t i) {
        uint8_t v = b ^ (kx ^ static_cast<uint8_t>(i * 7));
        v = static_cast<uint8_t>(v + (ka ^ static_cast<uint8_t>(i * 3)));
        uint8_t r = static_cast<uint8_t>((kr + (i & 7)) & 7);
        v = static_cast<uint8_t>((v << r) | (v >> ((8 - r) & 7)));
        v = sbox[v];
        return static_cast<uint8_t>(v - (ks ^ static_cast<uint8_t>(i * 5)));
    }
    KH_INLINE constexpr uint8_t enc_flavor_1(uint8_t b, uint8_t kx, uint8_t ka,
                                              uint8_t kr, uint8_t ks, size_t i) {
        uint8_t v = static_cast<uint8_t>(b - (ks ^ static_cast<uint8_t>(i * 5)));
        v = sbox[v];
        uint8_t r = static_cast<uint8_t>((kr + (i & 7)) & 7);
        v = static_cast<uint8_t>((v << r) | (v >> ((8 - r) & 7)));
        v = static_cast<uint8_t>(v + (ka ^ static_cast<uint8_t>(i * 3)));
        return v ^ (kx ^ static_cast<uint8_t>(i * 7));
    }
    KH_INLINE constexpr uint8_t enc_flavor_2(uint8_t b, uint8_t kx, uint8_t ka,
                                              uint8_t kr, uint8_t ks, size_t i) {
        uint8_t v = static_cast<uint8_t>(b + (ka ^ static_cast<uint8_t>(i * 3)));
        v = v ^ (kx ^ static_cast<uint8_t>(i * 7));
        v = sbox[v];
        v = static_cast<uint8_t>(v - (ks ^ static_cast<uint8_t>(i * 5)));
        uint8_t r = static_cast<uint8_t>((kr + (i & 7)) & 7);
        return static_cast<uint8_t>((v << r) | (v >> ((8 - r) & 7)));
    }
    KH_INLINE constexpr uint8_t enc_flavor_3(uint8_t b, uint8_t kx, uint8_t ka,
                                              uint8_t kr, uint8_t ks, size_t i) {
        uint8_t r = static_cast<uint8_t>((kr + (i & 7)) & 7);
        uint8_t v = static_cast<uint8_t>((b << r) | (b >> ((8 - r) & 7)));
        v = v ^ (kx ^ static_cast<uint8_t>(i * 7));
        v = static_cast<uint8_t>(v - (ks ^ static_cast<uint8_t>(i * 5)));
        v = sbox[v];
        return static_cast<uint8_t>(v + (ka ^ static_cast<uint8_t>(i * 3)));
    }

    KH_INLINE constexpr uint8_t enc_byte_by_flavor(int f, uint8_t b,
        uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        return (f==0)?enc_flavor_0(b,kx,ka,kr,ks,i):
               (f==1)?enc_flavor_1(b,kx,ka,kr,ks,i):
               (f==2)?enc_flavor_2(b,kx,ka,kr,ks,i):
                       enc_flavor_3(b,kx,ka,kr,ks,i);
    }

    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_flavor_0(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint8_t v;
        v = static_cast<uint8_t>(b + (ks ^ static_cast<uint8_t>(i * 5)));
        v = inv_sbox[v];
        uint8_t r = static_cast<uint8_t>((kr + (i & 7)) & 7);
        v = static_cast<uint8_t>((v >> r) | (v << ((8 - r) & 7)));
        v = static_cast<uint8_t>(v - (ka ^ static_cast<uint8_t>(i * 3)));
        return v ^ (kx ^ static_cast<uint8_t>(i * 7));
    }
    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_flavor_1(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint8_t v;
        v = b ^ (kx ^ static_cast<uint8_t>(i * 7));
        v = static_cast<uint8_t>(v - (ka ^ static_cast<uint8_t>(i * 3)));
        uint8_t r = static_cast<uint8_t>((kr + (i & 7)) & 7);
        v = static_cast<uint8_t>((v >> r) | (v << ((8 - r) & 7)));
        v = inv_sbox[v];
        return static_cast<uint8_t>(v + (ks ^ static_cast<uint8_t>(i * 5)));
    }
    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_flavor_2(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint8_t v;
        uint8_t r = static_cast<uint8_t>((kr + (i & 7)) & 7);
        v = static_cast<uint8_t>((b >> r) | (b << ((8 - r) & 7)));
        v = static_cast<uint8_t>(v + (ks ^ static_cast<uint8_t>(i * 5)));
        v = inv_sbox[v];
        v = v ^ (kx ^ static_cast<uint8_t>(i * 7));
        return static_cast<uint8_t>(v - (ka ^ static_cast<uint8_t>(i * 3)));
    }
    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_flavor_3(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint8_t v;
        v = static_cast<uint8_t>(b - (ka ^ static_cast<uint8_t>(i * 3)));
        v = inv_sbox[v];
        v = static_cast<uint8_t>(v + (ks ^ static_cast<uint8_t>(i * 5)));
        v = v ^ (kx ^ static_cast<uint8_t>(i * 7));
        uint8_t r = static_cast<uint8_t>((kr + (i & 7)) & 7);
        return static_cast<uint8_t>((v >> r) | (v << ((8 - r) & 7)));
    }

    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_call_0a(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint32_t lvl_a = _vol_a, lvl_b = _vol_b + (uint32_t)i;
        volatile uint8_t aux = (uint8_t)((lvl_a ^ lvl_b) & 0xFF); (void)aux;
        return dec_flavor_0(b, kx, ka, kr, ks, i);
    }
    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_call_0b(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint32_t s1 = _vol_c, s2 = _vol_d, s3 = s1 + s2; (void)s3;
        return dec_flavor_0(b, kx, ka, kr, ks, i);
    }
    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_call_1a(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint32_t p = _vol_e, q = _vol_f * 3U;
        volatile uint8_t r = (uint8_t)(p ^ q); (void)r;
        return dec_flavor_1(b, kx, ka, kr, ks, i);
    }
    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_call_1b(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint32_t x = _vol_a + _vol_c, y = _vol_b ^ _vol_d, z = x - y; (void)z;
        return dec_flavor_1(b, kx, ka, kr, ks, i);
    }
    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_call_2a(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint32_t m1 = _vol_e ^ (uint32_t)i, m2 = _vol_f + 7U, m3 = m1 * m2; (void)m3;
        return dec_flavor_2(b, kx, ka, kr, ks, i);
    }
    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_call_2b(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint32_t a = _vol_a * 11U, b1 = _vol_b ^ 0xA5A5A5A5U, c = a - b1; (void)c;
        return dec_flavor_2(b, kx, ka, kr, ks, i);
    }
    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_call_3a(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint32_t k = _vol_c + _vol_d, l = _vol_e * (uint32_t)(i + 1), m = k ^ l; (void)m;
        return dec_flavor_3(b, kx, ka, kr, ks, i);
    }
    KH_NOINLINE KH_HIDDEN
    static uint8_t dec_call_3b(uint8_t b, uint8_t kx, uint8_t ka, uint8_t kr, uint8_t ks, size_t i) {
        volatile uint32_t u = _vol_f ^ _vol_a, v = _vol_b + 13U, w = u * v; (void)w;
        return dec_flavor_3(b, kx, ka, kr, ks, i);
    }

    KH_NOINLINE KH_HIDDEN
    static uint8_t big_dispatch(int f, uint8_t b, uint8_t kx, uint8_t ka,
                                 uint8_t kr, uint8_t ks, size_t i, uint32_t mix) {
        volatile uint32_t sa = _vol_a, sb = _vol_b, sc = _vol_c;
        volatile uint32_t sd = _vol_d, se = _vol_e, sf = _vol_f;
        uint32_t blend = (sa^sb)+(sc*3U)-(sd<<1)+(se^sf);
        blend ^= mix; blend += (uint32_t)i;

        if (f == 0) {
            switch (blend & 7) {
                case 0: case 2: case 4: case 6: return dec_call_0a(b,kx,ka,kr,ks,i);
                default: return dec_call_0b(b,kx,ka,kr,ks,i);
            }
        } else if (f == 1) {
            switch (blend & 7) {
                case 0: case 2: case 4: case 6: return dec_call_1a(b,kx,ka,kr,ks,i);
                default: return dec_call_1b(b,kx,ka,kr,ks,i);
            }
        } else if (f == 2) {
            switch (blend & 7) {
                case 0: case 2: case 4: case 6: return dec_call_2a(b,kx,ka,kr,ks,i);
                default: return dec_call_2b(b,kx,ka,kr,ks,i);
            }
        } else {
            switch (blend & 7) {
                case 0: case 2: case 4: case 6: return dec_call_3a(b,kx,ka,kr,ks,i);
                default: return dec_call_3b(b,kx,ka,kr,ks,i);
            }
        }
    }

    template <size_t... I> struct Seq {};
    template <typename A, typename B> struct Cat;
    template <size_t... A, size_t... B> struct Cat<Seq<A...>, Seq<B...>> {
        using type = Seq<A..., (sizeof...(A) + B)...>;
    };
    template <size_t N> struct MakeSeq
        : Cat<typename MakeSeq<N/2>::type, typename MakeSeq<N - N/2>::type> {};
    template<> struct MakeSeq<0> { using type = Seq<>; };
    template<> struct MakeSeq<1> { using type = Seq<0>; };

    template <size_t N, uint32_t C, uint32_t L>
    class EncStr {
        using K = KeyGen<C, L>;
        static constexpr int F = K::FLAVOR;
        static constexpr size_t B = ((N + 16) / 16) * 16;
        static constexpr size_t PAD = (F==0)?B+16:(F==1)?B+32:(F==2)?B+48:B+64;
        alignas(16) uint8_t buf[PAD];
        size_t len;
    public:
        constexpr EncStr(const char*, Seq<>) : buf{}, len(N) {}
        template <size_t I, size_t... Rest>
        constexpr EncStr(const char* s, Seq<I, Rest...>) : EncStr(s, Seq<Rest...>()) {
            buf[I] = enc_byte_by_flavor(F, (uint8_t)s[I],
                K::key_xor, K::key_add, K::key_rot, K::key_sub, I);
        }
        KH_NOINLINE const char* decrypt() const {
            static thread_local uint8_t out[4096];
            volatile uint32_t va = _vol_a, vb = _vol_b, vc = _vol_c;
            volatile uint32_t vd = _vol_d, ve = _vol_e, vf = _vol_f;
            volatile uint32_t ex1=0, ex2=0, ex3=0;
            if(F>=1) ex1 = va*3U+vb;
            if(F>=2) ex2 = vc^vd+11U;
            if(F>=3) ex3 = ve-vf*5U;
            uint32_t mix = (va^vb)+(vc*3U)-(vd<<1)+(ve^vf)+ex1+ex2+ex3;

            volatile uint32_t ps = mix;
            const size_t PRE=(F==0)?3:(F==1)?5:(F==2)?7:9;
            for(size_t p=0;p<PRE;++p) {
                switch(p&3){case 0:ps=ps*1103515245U+12345U;break;
                case 1:ps=(ps^va)+0xDEADBEEFU;break;
                case 2:ps=(ps<<3)|(ps>>29);break;
                default:ps=ps-vb+vc;break;}
            }

            volatile uint32_t lane = ps^ve;
            uint32_t seed = (uint32_t)F*0x1000U+(uint32_t)K::key_aux1;
            for(size_t i=0;i<len;++i) {
                uint32_t ls = (lane+(uint32_t)i)&7;
                uint8_t r = big_dispatch(F, buf[i], K::key_xor, K::key_add,
                              K::key_rot, K::key_sub, i, seed^(ls*0x11U));
                out[i] = r;
                switch(lane&3){case 0:lane=lane*1103515245U+12345U;break;
                case 1:lane=(lane^va)+vb;break;
                case 2:lane=(lane<<5)|(lane>>27);break;
                default:lane=lane-vc+vd;break;}
            }
            out[len]=0;

            volatile uint32_t fin = lane;
            const size_t POST=(F==0)?5:(F==1)?3:(F==2)?7:9;
            for(size_t q=0;q<POST;++q) {
                switch(q&3){case 0:fin^=va;break;case 1:fin+=vb;break;
                case 2:fin*=31U;break;default:fin-=vc;break;}
            }
            _vol_a = (_vol_a ^ fin) | 1U;
            return reinterpret_cast<const char*>(out);
        }
    };

    template <typename T, uint32_t C, uint32_t L>
    class EncInt {
        using K = KeyGen<C, L>;
        static constexpr int F = K::FLAVOR;
        alignas(16) uint8_t buf[sizeof(T)];
    public:
        KH_INLINE EncInt(T v) : buf{} {
            const uint8_t* s = reinterpret_cast<const uint8_t*>(&v);
            for(size_t i=0;i<sizeof(T);++i)
                buf[i] = enc_byte_by_flavor(F, s[i],
                    K::key_xor, K::key_add, K::key_rot, K::key_sub, i);
        }
        KH_NOINLINE T decrypt() const {
            uint8_t loc[sizeof(T)];
            volatile uint32_t va=_vol_a,vb=_vol_b,vc=_vol_c,vd=_vol_d,ve=_vol_e,vf=_vol_f;
            volatile uint32_t ex1=0,ex2=0,ex3=0;
            if(F>=1)ex1=va*3U+vb;
            if(F>=2)ex2=vc^vd+11U;
            if(F>=3)ex3=ve-vf*5U;
            uint32_t mix=(va^vb)+(vc*3U)-(vd<<1)+(ve^vf)+ex1+ex2+ex3;

            volatile uint32_t ps=mix;
            const size_t PRE=(F==0)?3:(F==1)?5:(F==2)?7:9;
            for(size_t p=0;p<PRE;++p){switch(p&3){case 0:ps=ps*1103515245U+12345U;break;
            case 1:ps=(ps^va)+0xDEADBEEFU;break;case 2:ps=(ps<<3)|(ps>>29);break;
            default:ps=ps-vb+vc;break;}}

            volatile uint32_t lane=ps^ve;
            uint32_t seed=(uint32_t)F*0x1000U+(uint32_t)K::key_aux1;
            for(size_t i=0;i<sizeof(T);++i){
                uint32_t ls=(lane+(uint32_t)i)&7;
                loc[i]=big_dispatch(F,buf[i],K::key_xor,K::key_add,
                         K::key_rot,K::key_sub,i,seed^(ls*0x11U));
                switch(lane&3){case 0:lane=lane*1103515245U+12345U;break;
                case 1:lane=(lane^va)+vb;break;case 2:lane=(lane<<5)|(lane>>27);break;
                default:lane=lane-vc+vd;break;}
            }

            volatile uint32_t fin=lane;
            const size_t POST=(F==0)?5:(F==1)?3:(F==2)?7:9;
            for(size_t q=0;q<POST;++q){switch(q&3){case 0:fin^=va;break;
            case 1:fin+=vb;break;case 2:fin*=31U;break;default:fin-=vc;break;}}
            _vol_b=(_vol_b^fin)|1U;

            T r;for(size_t i=0;i<sizeof(T);++i)reinterpret_cast<uint8_t*>(&r)[i]=loc[i];
            return r;
        }
    };

    constexpr uint64_t _fnv(const char* s, uint64_t h = 14695981039346656037ULL) {
        return (*s==0)?h:_fnv(s+1,(h^static_cast<uint64_t>(*s))*1099511628211ULL);
    }
    KH_INLINE uintptr_t runtime_hash(const char* s) {
        uint64_t h=14695981039346656037ULL;
        while(*s){h^=static_cast<uint64_t>(*s++);h*=1099511628211ULL;}
        return static_cast<uintptr_t>(h);
    }

    template <typename F> union FltBits;
    template <> union FltBits<float>  { float f; uint32_t i; };
    template <> union FltBits<double> { double f; uint64_t i; };

} // namespace _kh_

#define KH_STR(s) \
    ([]() -> const char* { \
        constexpr size_t _n = sizeof(s) - 1; \
        static const auto _e = _kh_::EncStr<_n, __COUNTER__, __LINE__>( \
            s, typename _kh_::MakeSeq<_n>::type()); \
        return _e.decrypt(); \
    }())

#define KH_INT(v) \
    ([]() -> decltype(v) { \
        static const auto _e = _kh_::EncInt<decltype(v), __COUNTER__, __LINE__>(v); \
        return _e.decrypt(); \
    }())

#define KH_FLT(v) \
    ([]() -> decltype(v) { \
        using _FT = decltype(v); \
        _kh_::FltBits<_FT> _u; _u.f = (v); \
        using _IT = decltype(_u.i); \
        static const auto _e = _kh_::EncInt<_IT, __COUNTER__, __LINE__>(_u.i); \
        _kh_::FltBits<_FT> _r; _r.i = _e.decrypt(); \
        return _r.f; \
    }())

#define KH_HASH(s) (static_cast<uintptr_t>(_kh_::_fnv(s)))

#ifdef __OBJC__
#define KH_NS(s)  ([NSString stringWithUTF8String:KH_STR(s)])
#define KH_SEL(s) (sel_registerName(KH_STR(s)))
#define KH_CLS(s) (objc_getClass(KH_STR(s)))
#endif

#endif // KABRAXHIDE_H