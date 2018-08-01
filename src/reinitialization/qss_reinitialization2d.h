/******************************************************************************
 *
 *   Author:   Rahul Verma
 *   Copyright (c) 2018, The University of Texas at Austin. All rights reserved.
 *
 ******************************************************************************/
/*! \file qss_reinitialization2d.h
 *
 * Description: Header file for Fortran 77 2D reinitialization routines
 */

#ifndef INCLUDED_QSS_REINITIALIZATION_2D_H
#define INCLUDED_QSS_REINITIALIZATION_2D_H

#include "QSSLIB_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \file qss_reinitialization2d.h
 *
 * \brief
 * @ref qss_reinitialization2d.h provides support for computing the right-hand
 * side of the reinitialization and orthogonalization equations in two 
 * space dimensions.
 *
 */


/* Link between C/C++ and Fortran function names 
 *
 *      name in                      name in
 *      C/C++ code                   Fortran code
 *      ----------                   ------------
 */
#define COMPUTE_REINITIALIZATION_EQN_RHS_2D                              \
                                     computereinitializationeqnrhs2d_
#define QSS2D_COMPUTE_ORTHOGONALIZATION_EQN_RHS                             \
                                     qss2dcomputeorthogonalizationeqnrhs_
#define QSS2D_COMPUTE_DISTANCE_FOR_SUBCELL_FIX                              \
                                       qss2dcomputedistanceforsubcellfix_	
#define QSS2D_COMPUTE_REINITIALIZATION_EQN_RHS_SUBCELL_FIX_ORDER1           \
                      qss2dcomputereinitializationeqnrhssubcellfixorder1_
	

/*!
 * QSS2D_COMPUTE_REINITIALIZATION_EQN_RHS() computes the right-hand side 
 * of the reinitialization equation using a Godunov scheme to select the
 * numerical discretization of the \f$ sgn(\phi) |\nabla \phi| \f$ term.
 * Forward (plus) and backward (minus) spatial derivatives used in
 * the Godunov calculation must be supplied by the user.
 *
 * Arguments:
 *  - reinit_rhs (out):       right-hand side of reinitialization
 *                            equation
 *  - phi (in):               level set function at current iteration
 *                            of reinitialization process
 *  - phi0 (in):              level set function at initial iteration
 *                            iteration of reinitialization process
 *  - phi_*_plus (in):        forward spatial derivatives for 
 *                            \f$ \nabla \phi \f$
 *  - phi_*_minus (in):       backward spatial derivatives for 
 *                            \f$ \nabla \phi \f$
 *  - use_phi0_for_sgn (in):  flag to specify whether \f$ \phi_0 \f$ should 
 *                            be used in the computation of \f$ sgn(\phi) \f$.
 *                              0 = use \f$ \phi \f$ (do NOT use 
 *                                  \f$ \phi_0 \f$ );
 *                              1 = use \f$ \phi_0 \f$.
 *  - *_gb (in):              index range for ghostbox
 *  - *_fb (in):              index range for fillbox
 *
 * NOTES:
 * - if use_phi0_for_sgn is not equal to 0 or 1, the default
 *   behavior of QSS2D_COMPUTE_REINITIALIZATION_EQN_RHS() is to use
 *   \f$ \phi \f$ (i.e. equivalent to setting use_phi0_for_sgn to 0)
 *
 */
void COMPUTE_REINITIALIZATION_EQN_RHS_2D(
  QSSLIB_REAL *reinit_rhs,
  const QSSLIB_REAL* phi,
  const QSSLIB_REAL* phi0,
  const int *ilo_phi0_gb, 
  const int *ihi_phi0_gb, 
  const int *jlo_phi0_gb, 
  const int *jhi_phi0_gb,
  const int *ilo_fb,   
  const int *ihi_fb,
  const int *jlo_fb,   
  const int *jhi_fb,
  const QSSLIB_REAL *dx, 
  const QSSLIB_REAL *dy,
  const int *use_phi0_for_sgn);


/*!
 * QSS2D_COMPUTE_ORTHOGONALIZATION_EQN_RHS() computes the right-hand side
 * of the orthogonalization equation:
 *
 * \f[
 *
 *   \phi_t + \nabla \phi \cdot 
 *      \left ({ \frac{sgn(\psi)}{|\nabla \psi|} \nabla \psi }\right) = 0
 *
 * \f]
 *
 * Upwinding is used to select whether the forward (plus) or backward
 * (minus) spatial derivative should be used for \f$ \nabla \phi\f$.  
 * \f$ \nabla \psi \f$ is computed by averaging the forward and backward 
 * spatial derivatives for \f$ \nabla \psi \f$.  Forward and backward 
 * spatial derivatives used in the calculation must be supplied by the user.
 *
 * Arguments:
 *  - othro_rhs (out):        right-hand side of orthogonalization
 *                            equation
 *  - psi (in):               data array for \f$ \psi \f$
 *  - phi_*_plus (in):        forward spatial derivatives for 
 *                            \f$ \nabla \phi \f$
 *  - phi_*_minus (in):       backward spatial derivatives for
 *                            \f$ \nabla \phi \f$
 *  - psi_*_plus (in):        forward spatial derivatives for 
 *                            \f$ \nabla \psi \f$
 *  - psi_*_minus (in):       backward spatial derivatives for
 *                            \f$ \nabla \psi \f$
 *  - *_gb (in):              index range for ghostbox
 *  - *_fb (in):              index range for fillbox
 *
 *  Return value:             none
 */
void QSS2D_COMPUTE_ORTHOGONALIZATION_EQN_RHS(
  QSSLIB_REAL *ortho_rhs,
  const int *ilo_rhs_gb, 
  const int *ihi_rhs_gb, 
  const int *jlo_rhs_gb, 
  const int *jhi_rhs_gb,
  const QSSLIB_REAL *phi_x_plus, 
  const QSSLIB_REAL *phi_y_plus,
  const int *ilo_grad_phi_plus_gb,   
  const int *ihi_grad_phi_plus_gb,
  const int *jlo_grad_phi_plus_gb,   
  const int *jhi_grad_phi_plus_gb,
  const QSSLIB_REAL *phi_x_minus, 
  const QSSLIB_REAL *phi_y_minus,
  const int *ilo_grad_phi_minus_gb,   
  const int *ihi_grad_phi_minus_gb,
  const int *jlo_grad_phi_minus_gb,   
  const int *jhi_grad_phi_minus_gb,
  const QSSLIB_REAL* psi,
  const int *ilo_psi_gb, 
  const int *ihi_psi_gb, 
  const int *jlo_psi_gb, 
  const int *jhi_psi_gb,
  const QSSLIB_REAL *psi_x_plus, 
  const QSSLIB_REAL *psi_y_plus,
  const int *ilo_grad_psi_plus_gb,   
  const int *ihi_grad_psi_plus_gb,
  const int *jlo_grad_psi_plus_gb,   
  const int *jhi_grad_psi_plus_gb,
  const QSSLIB_REAL *psi_x_minus, 
  const QSSLIB_REAL *psi_y_minus,
  const int *ilo_grad_psi_minus_gb,   
  const int *ihi_grad_psi_minus_gb,
  const int *jlo_grad_psi_minus_gb,   
  const int *jhi_grad_psi_minus_gb,
  const int *ilo_fb,   
  const int *ihi_fb,
  const int *jlo_fb,   
  const int *jhi_fb,
  const QSSLIB_REAL *dx, 
  const QSSLIB_REAL *dy);


/*!
*  QSS2D_COMPUTE_DISTANCE_FOR_SUBCELL_FIX  determines whether each 
*  gridpoint is close to the interface (within one cell) and if so, 
*  computes the distance that is used in subcell fix to reinitialization. 
*  Following Russo, Smereka: "A Remark on Computing Distance Functions", 
*  J Comp Phys, 2000.
*
*  This ought to be done only once for phi0 and provided to routine
*  QSS2D_COMPUTE_REINITIALIZATION_EQN_RHS_SUBCELL_FIX_ORDER1
*  Implementation note: still not sure if it's worth storing another array
*  for this or recompute every time... 
*
*  Distance of functions away from the interface is set to a large negative 
*  number.
*
*  Arguments
*    distance0(out):         distance computed for phi0
*    phi0 (in):              level set function at initial iteration
*                            iteration of reinitialization process
*    *_gb (in):              index range for ghostbox
*    *_fb (in):              index range for fillbox
*    d* (in):                grid spacing
*/

 void QSS2D_COMPUTE_DISTANCE_FOR_SUBCELL_FIX(
  QSSLIB_REAL* distance0, 
  const QSSLIB_REAL* phi0,
  const int *ilo_phi0_gb, 
  const int *ihi_phi0_gb, 
  const int *jlo_phi0_gb, 
  const int *jhi_phi0_gb,
  const int *ilo_fb,   
  const int *ihi_fb,
  const int *jlo_fb,   
  const int *jhi_fb,
  const QSSLIB_REAL *dx, 
  const QSSLIB_REAL *dy);  

/*!
*  QSS2D_COMPUTE_REINITIALIZATION_EQN_RHS_SUBCELL_FIX_ORDER1() computes the right-hand 
*  side of the reinitialization equation.  Following 
*  Russo, Smereka: "A Remark on Computing Distance Functions", J Comp Phys,
*  2000.
*  1) Away from the interface 
*     It is using a Godunov scheme to select the 
*     numerical discretization of the sgn(phi) |grad(phi)| term.
*     Forward (plus) and backward (minus) spatial derivatives used in 
*     the Godunov calculation must be supplied by the user.
*  2) Near interface a correction (of first order) is made in order
*     not to use the information from the opposite side of the interface.
* 
*
*  Arguments:
*    reinit_rhs (out):       right-hand side of reinitialization 
*                            equation
*    phi (in):               level set function at current iteration
*                            of reinitialization process
*    phi0 (in):              level set function at initial iteration
*                            iteration of reinitialization process
*    distance0(in):           distance computed by lsm2dComputeDistanceSubcellFix
*                            at the beginning of reinitialization process
*    phi_*_plus (in):        forward spatial derivatives for grad(phi)
*    phi_*_minus (in):       backward spatial derivatives for grad(phi)
*    *_gb (in):              index range for ghostbox
*    *_fb (in):              index range for fillbox
*    d* (in):                grid spacing
*/
  void QSS2D_COMPUTE_REINITIALIZATION_EQN_RHS_SUBCELL_FIX_ORDER1(
  QSSLIB_REAL *reinit_rhs,
  const QSSLIB_REAL* phi,
  const int *ilo_phi_gb, 
  const int *ihi_phi_gb, 
  const int *jlo_phi_gb, 
  const int *jhi_phi_gb,
  const QSSLIB_REAL* phi0,
  const QSSLIB_REAL* distance0,
  const int *ilo_fb,   
  const int *ihi_fb,
  const int *jlo_fb,   
  const int *jhi_fb,
  const QSSLIB_REAL *dx, 
  const QSSLIB_REAL *dy);
  
#ifdef __cplusplus
}
#endif

#endif
