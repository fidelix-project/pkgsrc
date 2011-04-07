$NetBSD: patch-src_network_ssl_qsslsocket_openssl.cpp,v 1.2 2011/04/07 05:23:52 obache Exp $

From b87528a71b66e786c11804d7b79e408aae612748 Mon Sep 17 00:00:00 2001
From: Peter Hartmann <peter.hartmann@nokia.com>
Date: Fri, 25 Mar 2011 13:45:24 +0100
Subject: [PATCH] QSslSocket internals: abort on encountering blacklisted certificates

tested manually with "openssl s_server -cert blacklisted.pem -key
key.pem" and connecting a QSslSocket.

Reviewed-by: Markus Goetz
Task-number: QTBUG-18338
---
 src/network/ssl/qsslsocket_openssl.cpp |    7 +++++++
 1 files changed, 7 insertions(+), 0 deletions(-)

diff --git a/src/network/ssl/qsslsocket_openssl.cpp b/src/network/ssl/qsslsocket_openssl.cpp
index 0866534..2427193 100644
--- src/network/ssl/qsslsocket_openssl.cpp
+++ src/network/ssl/qsslsocket_openssl.cpp
@@ -1193,6 +1193,13 @@ bool QSslSocketBackendPrivate::startHandshake()
     X509 *x509 = q_SSL_get_peer_certificate(ssl);
     configuration.peerCertificate = QSslCertificatePrivate::QSslCertificate_from_X509(x509);
     q_X509_free(x509);
+    if (QSslCertificatePrivate::isBlacklisted(configuration.peerCertificate)) {
+        q->setErrorString(QSslSocket::tr("The peer certificate is blacklisted"));
+        q->setSocketError(QAbstractSocket::SslHandshakeFailedError);
+        emit q->error(QAbstractSocket::SslHandshakeFailedError);
+        plainSocket->disconnectFromHost();
+        return false;
+    }
 
     // Start translating errors.
     QList<QSslError> errors;
