#include "files.h"
#include "test/ff.h"
#include "test/rt.h"
#include "test/test.h"

using namespace TINKER_NAMESPACE;
using namespace test;

static const char* strbndterm_only = R"**(
strbndterm  only
)**";

static int usage = calc::xyz | calc::vmask;

static const double ref_g_strbnd_trpcage[][3] = {
    {0.3985, 0.4851, 1.3054},    {1.0413, 0.9150, -1.2830},
    {-0.7165, -1.3450, -3.0194}, {-0.8970, 0.5968, 0.9090},
    {-0.0457, 0.0220, -0.0536},  {0.0218, 0.1323, -0.1287},
    {-0.3254, -0.1868, -0.1747}, {0.5484, -0.8708, -0.2298},
    {0.5112, -1.4113, 0.0967},   {0.3534, -0.9304, -0.0431},
    {-0.4956, 0.5295, -0.1476},  {0.0876, 0.1132, 0.6539},
    {-0.4777, 1.0049, 0.5774},   {-0.4724, -0.1688, 0.0055},
    {-0.0951, 0.0977, -0.0168},  {-0.0930, 0.0216, -0.2307},
    {2.5345, 0.9395, 2.9306},    {-2.7802, 0.0518, -0.4903},
    {-1.8923, 0.5503, -1.7196},  {1.0738, -0.3056, -0.1008},
    {0.2690, -0.1626, -0.3258},  {-0.4896, 0.5578, 0.2607},
    {0.6520, -1.1697, -0.7194},  {1.2994, -0.1364, -0.5385},
    {-0.5474, -1.4147, 1.3830},  {0.6786, -0.8151, -0.6405},
    {0.0613, -0.1592, -0.4016},  {-0.3689, 0.2093, 1.1764},
    {-1.0016, 2.0767, -0.3903},  {0.2246, 0.1671, -0.1824},
    {0.0495, 0.4139, -0.2812},   {0.1750, 0.1203, -0.2557},
    {-0.0333, 0.1632, 0.2529},   {-0.1824, 0.0119, 0.4470},
    {-0.1280, 0.4177, 0.2197},   {1.1715, -0.4993, 2.6375},
    {0.6957, 0.2276, -1.5031},   {-0.4327, -0.5439, -2.3480},
    {-0.7514, 0.2186, 0.9426},   {-0.3634, 0.0711, 0.0841},
    {0.5330, -0.5541, -0.3928},  {0.0319, 0.3905, 0.8796},
    {-0.0849, -0.3554, 0.9733},  {1.4341, -0.8782, -0.1337},
    {-1.2934, 0.6763, 0.5113},   {1.0446, -0.5790, -0.4852},
    {-0.4564, 0.3727, -0.7526},  {-0.8867, 0.8363, -2.0536},
    {-0.7239, 0.3397, 0.8998},   {-0.3717, 0.0815, 0.1248},
    {0.2148, -0.1887, -0.0247},  {0.0636, -0.0571, 0.1004},
    {-0.0758, 0.0157, 0.1687},   {0.0603, -0.0293, -0.0722},
    {-0.0224, 0.0153, -0.0258},  {0.8222, -0.5635, 0.3233},
    {1.6798, 0.3610, 2.1309},    {-1.0531, -0.4417, -1.3548},
    {-1.9238, -0.1040, -0.5723}, {1.1575, -0.1596, -0.1346},
    {0.2124, -0.0322, -0.2447},  {-1.0053, 0.7031, 0.3842},
    {0.6489, -0.9540, -1.9561},  {-0.0689, -0.5721, -0.6000},
    {0.2456, -0.1250, -0.5340},  {0.4535, -0.2244, 0.2437},
    {-0.0956, 0.2425, 2.7354},   {-0.3837, 0.8260, 0.3830},
    {0.2764, -0.1410, -0.2826},  {-0.2844, 0.1907, 0.0403},
    {-0.1326, 0.3799, 0.0101},   {-0.2051, 0.2356, 0.2343},
    {0.0951, 0.1300, -0.0642},   {-0.0571, 0.3369, -0.0182},
    {0.0746, 0.1116, -0.1582},   {0.9455, -0.2261, 2.7033},
    {-0.4066, 0.1124, -1.8514},  {0.5137, -0.1599, -1.9337},
    {-0.8521, 0.1774, 1.0385},   {-0.3406, 0.0317, 0.0842},
    {0.7142, -0.7497, -0.5376},  {-0.7553, 1.3984, -2.2853},
    {0.2634, 0.5851, 2.2298},    {-1.2093, -0.7836, 1.5585},
    {0.7275, -0.0596, -1.0276},  {-0.2406, -0.5459, 0.0739},
    {-0.4484, 0.1612, 0.2539},   {1.1030, -0.2187, 0.2533},
    {0.5082, -0.6771, -0.4741},  {-0.3512, 0.1254, -0.0051},
    {0.0291, -0.0246, -0.0462},  {0.1303, 0.2080, -0.0871},
    {1.8847, 0.4700, 1.7326},    {-1.4114, -0.0471, -0.8517},
    {-1.6466, 0.0307, -0.6529},  {1.0021, -0.0494, -0.2622},
    {0.1439, -0.0237, -0.1991},  {-0.8101, 0.6329, 0.4231},
    {0.0412, -0.9498, 0.0347},   {5.5218, 1.5310, 0.9868},
    {-4.0879, 1.4671, 3.0855},   {2.3949, -2.2766, -4.4634},
    {2.3042, -2.9672, -5.2541},  {-6.7753, -0.7434, 0.3009},
    {-2.2197, 2.1839, 4.2200},   {1.9876, 4.8955, 7.4034},
    {-0.4016, -0.2307, -0.4385}, {0.4747, -0.2238, -0.3532},
    {0.1744, 0.0459, -0.2454},   {-0.0892, 0.1839, 0.4092},
    {0.0209, -0.2278, -0.3729},  {-0.0287, 0.0253, 0.0475},
    {2.6477, 0.4257, 0.0314},    {-2.4562, -0.5829, -0.3334},
    {2.0552, -1.1667, -2.4071},  {-1.1238, -1.7712, -2.6400},
    {1.1442, -0.2580, 2.6010},   {-0.3572, -0.2079, -2.3657},
    {0.2502, -0.1339, -1.6746},  {-0.7699, 0.1921, 1.0625},
    {-0.3553, -0.0062, 0.1215},  {0.5892, -0.5304, -0.5216},
    {-0.9699, 1.4500, 0.2876},   {-0.8728, -0.3931, 1.0666},
    {1.3148, 1.6019, 0.1387},    {-1.0978, 0.6832, 0.2551},
    {-0.3941, 0.0656, -0.0620},  {1.2276, -0.0929, 0.1620},
    {0.3371, -1.7976, -1.2694},  {-0.2415, -0.2359, 0.1349},
    {-0.2253, -0.3933, -0.0774}, {-0.3113, -0.1749, 0.0371},
    {0.2611, -0.1440, 0.1033},   {0.4687, 0.0525, 0.0168},
    {0.2903, -0.2894, -0.0272},  {2.3634, 0.4027, 1.5902},
    {-2.1348, -0.6978, -0.7627}, {-1.2730, 0.2965, -0.6429},
    {0.8232, -0.3310, -0.1757},  {0.1338, -0.0473, -0.2035},
    {-0.8148, 0.8197, 0.4121},   {-0.5733, -1.1590, -1.7653},
    {1.2369, 0.8432, -0.4818},   {-0.3117, -0.5491, 0.0138},
    {0.3312, -0.2534, 0.5330},   {0.1589, -0.3600, 0.3083},
    {0.3837, -0.2226, -0.3516},  {-0.2049, 0.4354, 1.4440},
    {-0.3497, -0.5837, 0.8771},  {-0.3491, 0.6099, -0.3565},
    {0.3751, 0.5541, -0.7144},   {-0.1037, -0.2101, 0.2270},
    {0.2627, 0.0287, -0.0200},   {-0.1839, 0.6115, -0.0411},
    {0.1523, 0.0517, 0.1296},    {0.1253, 0.2909, -0.0951},
    {-0.1518, 0.1901, 0.0726},   {0.5234, -0.6971, 1.5679},
    {-0.6333, -0.3114, -0.9465}, {0.3295, 1.1364, -1.8606},
    {-0.4089, -0.7154, 1.0819},  {-0.2477, 0.0982, 0.0692},
    {1.2530, 0.3904, -0.5503},   {0.0374, -1.0967, 2.5485},
    {-0.0140, 0.3320, 1.7439},   {-4.2514, 1.0408, -1.3805},
    {4.0543, -0.9538, -2.9235},  {-0.3160, -0.3851, 0.1408},
    {0.4196, 0.5376, 0.3228},    {-1.0360, -2.2149, -0.6323},
    {0.0591, 3.1147, 0.7545},    {0.0317, 2.3591, 2.2725},
    {0.0639, -1.3169, -1.1958},  {0.1598, 0.5324, -0.3062},
    {-0.5815, -0.3504, 0.1180},  {0.7082, -0.4654, -0.3764},
    {0.1218, -1.4613, -0.0634},  {-0.4895, -1.8637, -1.0305},
    {2.5331, 0.6944, -0.3625},   {-1.0528, -0.1721, 0.8381},
    {0.0084, 0.1260, 0.1517},    {-0.4013, -0.1099, 0.2422},
    {-0.4285, 1.0387, 0.1749},   {0.4532, 0.4972, -0.0716},
    {-1.4653, 0.7358, 1.4324},   {-0.0253, -1.3142, -0.1384},
    {0.4105, 0.7534, -0.0351},   {-0.0745, -0.3975, 0.2293},
    {-0.7995, -0.2240, -2.3630}, {0.8814, -0.6052, -0.6311},
    {0.5250, 0.0905, 0.2365},    {0.5314, 0.5246, 0.6118},
    {0.0205, 0.0308, 0.2791},    {-0.0240, 0.1086, 0.0739},
    {-0.4834, 0.1309, 0.8241},   {-0.3032, 0.0233, 0.0460},
    {-0.1994, 0.0982, 0.0168},   {1.6782, -0.7994, 0.2758},
    {-1.3140, 0.3805, 0.3056},   {-0.9695, 1.5058, 0.0029},
    {0.3416, -1.3216, -0.0368},  {-0.1189, -0.3000, -0.0308},
    {0.2717, 1.0866, -0.8846},   {-0.8711, -0.2788, 0.7584},
    {0.4198, -0.3834, -0.1159},  {0.1301, 0.2427, -0.4444},
    {0.2601, 0.1230, -0.0985},   {0.1048, -0.1925, -0.1683},
    {1.6323, 0.2405, 0.5971},    {-0.8671, 0.1584, -0.7692},
    {-0.5536, -0.9320, -0.9865}, {0.3374, 0.8954, 0.4891},
    {-0.0854, 0.2595, 0.0430},   {-0.5388, -1.2479, 0.6786},
    {-0.0096, 0.3813, -1.3318},  {0.2449, 0.3581, 0.5155},
    {-0.2394, -0.1782, 0.3953},  {0.1509, -0.1912, 0.2815},
    {0.0200, 0.1316, 0.2362},    {0.4916, 0.0893, 0.2199},
    {-0.5236, -0.2885, -0.7555}, {0.3820, 1.4337, 0.5685},
    {0.1818, -0.8885, -0.0935},  {-0.0161, -0.2375, -0.1166},
    {0.0101, -0.0177, -0.1876},  {-0.2376, -0.0934, 0.3219},
    {1.8900, 0.6843, 0.9477},    {-2.4093, -1.1113, -0.0503},
    {-1.1432, -1.7197, -0.4319}, {0.3731, 1.7826, 0.1564},
    {-0.0710, 0.2774, 0.0359},   {-0.1556, -0.8347, 0.0011},
    {-0.3799, 0.4673, -2.2677},  {0.6694, -0.1275, 0.6477},
    {0.5960, -0.6347, -0.6944},  {0.7256, -1.1213, -1.0589},
    {1.6041, 0.1253, 0.9812},    {-0.8003, -0.0402, -0.4335},
    {-0.4808, 0.2801, 0.2762},   {-0.0333, 0.9503, 0.0647},
    {0.3857, -0.7375, 0.1295},   {0.2831, -0.0009, -0.0550},
    {-0.8942, 0.1965, 0.5796},   {-0.0634, 0.8502, 0.5580},
    {-0.2995, -0.1484, 0.2619},  {-0.7535, 0.4788, 0.5629},
    {0.0829, 0.0195, 0.0737},    {-0.0055, 0.0545, 0.0914},
    {-0.0471, 0.0197, 0.0113},   {0.0423, 0.0166, 0.0589},
    {1.8502, -1.1436, -0.3317},  {-0.1023, 2.8642, -0.0472},
    {-1.1676, 1.4300, 2.3881},   {0.8372, -1.0413, -1.6870},
    {0.0724, -0.0574, -0.0817},  {-2.1396, -0.6539, -0.7349},
    {-0.4140, -0.8112, 0.4437},  {0.6453, 0.0107, 0.0887},
    {0.8523, -0.1765, -0.1728},  {0.2531, 0.1396, 0.1905},
    {0.0790, 0.0496, -0.1532},   {0.4449, 0.7340, 0.0318},
    {-0.1883, 0.3006, -0.2125},  {-0.0430, 0.1741, -0.0684},
    {-0.1143, -1.5442, 0.9485},  {0.4949, -1.4770, -2.7919},
    {1.8175, 1.8647, 0.1680},    {-1.1293, -1.1422, 0.4431},
    {0.3288, -0.0186, -0.0391},  {-1.5751, 2.1589, -0.3695},
    {0.0542, 0.8534, 0.7556},    {0.2327, -0.4524, 0.3133},
    {-0.0158, -0.7857, 0.4919},  {0.3073, -0.1806, 0.0372},
    {-0.1153, -0.1431, -0.0576}, {0.3720, -0.6255, -0.5210},
    {-0.1075, 0.0097, -0.3409},  {-0.0974, -0.0434, -0.1573},
    {0.6266, 0.6071, 1.0375},    {-0.5264, -1.0616, 0.5508},
    {-1.6779, -1.1931, -0.6486}, {0.1485, 0.5665, 0.2101},
    {0.0515, -0.3123, -0.0126},  {-0.0058, 0.2745, -2.0971},
    {0.6772, -0.0142, -0.3845},  {0.0997, -0.2467, 0.6622},
    {0.1493, 0.3901, 1.0243},    {-0.0762, 0.0521, 0.2387},
    {-0.1231, 0.1584, 0.0856},   {-0.4506, -0.3766, 0.4422},
    {-0.4009, 0.0126, -0.1865},  {-0.1782, 0.0768, -0.0333},
    {1.9630, 0.9330, 0.7705},    {1.9230, 4.1693, 3.1703},
    {-1.2276, -1.3661, -0.3887}, {3.2600, -2.9952, -1.3415},
    {0.0811, -0.4933, -0.2378},  {-0.4632, 0.9094, -0.7597},
    {0.3881, -1.0727, 0.3141},   {-0.2190, 0.7281, 0.3998},
    {0.0242, 0.1653, -0.3613},   {0.1551, 0.1649, -0.1332},
    {-0.1380, -0.5422, -0.6618}, {-4.1085, 0.3956, -0.2928}};
TEST_CASE("Strbnd-Trpcage", "[ff][estrbnd][trpcage]") {
  const char* k = "test_trpcage.key";
  const char* x1 = "test_trpcage.xyz";
  const char* p = "amoebapro13.prm";

  std::string k0 = trpcage_key;
  k0 += strbndterm_only;
  file fke(k, k0);

  file fx1(x1, trpcage_xyz);
  file fpr(p, amoebapro13_prm);

  const char* argv[] = {"dummy", x1};
  int argc = 2;
  test_begin_1_xyz(argc, argv);
  use_data = usage;
  initialize();

  const double eps_e = 0.0001;
  const double ref_e = -0.6930;
  const int ref_count = 504;
  const double eps_g = test_get_eps2(0.0003, 0.0001);
  const double eps_v = 0.001;
  const double ref_v[][3] = {{-55.818, 18.525, 25.157},
                             {18.525, -26.515, -9.871},
                             {25.157, -9.871, -15.485}};

  COMPARE_BONDED_FORCE(estrbnd, eba, ref_e, eps_e, nstrbnd, ref_count, gx, gy,
                       gz, ref_g_strbnd_trpcage, eps_g, vir_eba, ref_v, eps_v);

  finish();
  test_end();
}
