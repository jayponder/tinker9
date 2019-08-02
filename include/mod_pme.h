#ifndef TINKER_MOD_PME_H_
#define TINKER_MOD_PME_H_

#include "util_rc_man.h"

TINKER_NAMESPACE_BEGIN
template <class T>
class GeneralUnit {
private:
  int unit_;

public:
  GeneralUnit()
      : unit_(-1) {}

  GeneralUnit(int u)
      : unit_(u) {}

  bool operator<(const GeneralUnit<T>& u) const { return unit_ < u.unit_; }

  bool operator==(const GeneralUnit<T>& u) const { return unit_ == u.unit_; }

  int unit() const { return unit_; }

public:
  static std::vector<T>& all_objs() {
    static std::vector<T> o;
    return o;
  }

  static std::vector<T*>& all_deviceptrs() {
    static std::vector<T*> o;
    return o;
  }
};

/**
 * pme.f and kewald.f
 *
 * allocate igrid(3,n)                   !! integer
 * allocate (bsmod1(nfft1))              !! real*8
 * allocate (bsmod2(nfft2))              !! real*8
 * allocate (bsmod3(nfft3))              !! real*8
 * allocate (bsbuild(bsorder,bsorder))   !! real*8
 * allocate (thetai1(4,bsorder,n))       !! real*8
 * allocate (thetai2(4,bsorder,n))       !! real*8
 * allocate (thetai3(4,bsorder,n))       !! real*8
 * allocate (qgrid(2,nfft1,nfft2,nfft3)) !! real*8
 * allocate (qfac(nfft1,nfft2,nfft3))    !! real*8
 */
struct pme_t {
  real aewald;
  int nfft1, nfft2, nfft3, bsorder;
  int* igrid;                     // deviceptr
  real *bsmod1, *bsmod2, *bsmod3; // deviceptr
  real* qgrid;                    // deviceptr
};

typedef GeneralUnit<pme_t> PMEUnit;

TINKER_EXTERN PMEUnit epme_unit; // electrostatic
TINKER_EXTERN PMEUnit ppme_unit; // polarization
TINKER_EXTERN PMEUnit dpme_unit; // dispersion

TINKER_EXTERN PMEUnit pvpme_unit; // polarization virial

TINKER_EXTERN double ewald_switch_cut, ewald_switch_off;

TINKER_EXTERN real (*cmp)[10];
TINKER_EXTERN real (*fmp)[10];
TINKER_EXTERN real (*cphi)[10];
TINKER_EXTERN real (*fphi)[20];

TINKER_EXTERN real (*fuind)[3];
TINKER_EXTERN real (*fuinp)[3];
TINKER_EXTERN real (*fdip_phi1)[10];
TINKER_EXTERN real (*fdip_phi2)[10];
TINKER_EXTERN real (*cphidp)[10];
TINKER_EXTERN real (*fphidp)[20];

TINKER_EXTERN real* vir_m;

void pme_data(rc_op op);

pme_t& pme_obj(PMEUnit pme_u);
pme_t* pme_deviceptr(PMEUnit pme_u);

/// This function must be called after pme_data has been called because it
/// needs to know the number of pme objects created.
void fft_data(rc_op op);
void fftfront(PMEUnit pme_u);
void fftback(PMEUnit pme_u);

int use_ewald();
void pme_init(int vers);
TINKER_NAMESPACE_END

TINKER_NAMESPACE_BEGIN
/**
 * @brief
 * make the scalar summation over reciprocal lattice
 */
void pme_conv0(PMEUnit pme_u);                 // without virial
void pme_conv1(PMEUnit pme_u, real* gpu_vir9); // with virial

void rpole_to_cmp();
/**
 * @brief
 * Input: cmp, cartesian rotated mpole.
 * Output: fmp, fractional rotated mpole.
 */
void cmp_to_fmp(PMEUnit pme_u, const real (*cmp)[10], real (*fmp)[10]);
void cuind_to_fuind(PMEUnit pme_u, const real (*cind)[3], const real (*cinp)[3],
                    real (*fuind)[3], real (*fuinp)[3]);
/**
 * @brief
 * Input: fphi.
 * Output: cphi.
 */
void fphi_to_cphi(PMEUnit pme_u, const real (*fphi)[20], real (*cphi)[10]);
/**
 * @brief
 * Input: fmp.
 * Output: qgrid.
 */
void grid_mpole(PMEUnit pme_u, real (*gpu_fmp)[10]);
/**
 * @brief
 * Input: qgrid.
 * Output: fphi.
 */
void fphi_mpole(PMEUnit pme_u, real (*gpu_fphi)[20]);

void grid_uind(PMEUnit pme_u, real (*gpu_find)[3], real (*gpu_finp)[3]);
void fphi_uind(PMEUnit pme_u, real (*gpu_fdip_phi1)[10],
               real (*gpu_fdip_phi2)[10], real (*gpu_fdip_sum_phi)[20]);
void fphi_uind2(PMEUnit pme_u, real (*gpu_fdip_phi1)[10],
                real (*gpu_fdip_phi2)[10]);
TINKER_NAMESPACE_END

#endif
