$NetBSD: patch-src_radeon__driver.c,v 1.2 2015/04/02 22:16:46 tnn Exp $

--- src/radeon_driver.c.orig	2012-06-25 08:19:41.000000000 +0000
+++ src/radeon_driver.c
@@ -178,7 +178,7 @@ static const OptionInfoRec RADEONOptions
     { OPTION_SCALER_WIDTH,                "ScalerWidth",              OPTV_INTEGER, {0}, FALSE }, 
 #endif
 #ifdef RENDER
-    { OPTION_RENDER_ACCEL,   "RenderAccel",      OPTV_BOOLEAN, {0}, FALSE },
+    { OPTION_RENDER_ACCEL,   "RenderAccel",      OPTV_BOOLEAN, {0}, TRUE },
     { OPTION_SUBPIXEL_ORDER, "SubPixelOrder",    OPTV_ANYSTR,  {0}, FALSE },
 #endif
     { OPTION_CLOCK_GATING,   "ClockGating",      OPTV_BOOLEAN, {0}, FALSE },
@@ -3761,7 +3761,8 @@ Bool RADEONScreenInit(SCREEN_INIT_ARGS_D
 
     /* DRI finalisation */
 #ifdef XF86DRI
-    if (info->directRenderingEnabled && info->cardType==CARD_PCIE &&
+    if (info->directRenderingEnabled &&
+	(info->cardType==CARD_PCIE || info->cardType==CARD_PCI) &&
         info->dri->pKernelDRMVersion->version_minor >= 19)
     {
       if (RADEONDRISetParam(pScrn, RADEON_SETPARAM_PCIGART_LOCATION, info->dri->pciGartOffset) < 0)
@@ -6440,7 +6441,11 @@ static Bool RADEONCloseScreen(CLOSE_SCRE
     if (info->dri && info->dri->pDamage) {
 	PixmapPtr pPix = pScreen->GetScreenPixmap(pScreen);
 
+#ifdef PKGSRC_LEGACY_XORG_SERVER
 	DamageUnregister(&pPix->drawable, info->dri->pDamage);
+#else
+	DamageUnregister(info->dri->pDamage);
+#endif
 	DamageDestroy(info->dri->pDamage);
 	info->dri->pDamage = NULL;
     }
