$NetBSD: patch-src_pkcs11_pkcs11-global.c,v 1.3 2014/03/14 20:49:56 gdt Exp $

Use correct size for malloc.

Not yet reported upstream.

--- src/pkcs11/pkcs11-global.c.orig	2012-12-04 14:43:40.000000000 +0000
+++ src/pkcs11/pkcs11-global.c
@@ -42,7 +42,7 @@ extern CK_FUNCTION_LIST pkcs11_function_
 #include <pthread.h>
 CK_RV mutex_create(void **mutex)
 {
-	pthread_mutex_t *m = malloc(sizeof(*mutex));
+	pthread_mutex_t *m = malloc(sizeof(*m));
 	if (m == NULL)
 		return CKR_GENERAL_ERROR;;
 	pthread_mutex_init(m, NULL);
