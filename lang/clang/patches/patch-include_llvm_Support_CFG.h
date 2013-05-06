$NetBSD: patch-include_llvm_Support_CFG.h,v 1.1 2013/05/06 14:50:30 joerg Exp $

LLVM r178240: Fix iterator interface.

--- include/llvm/Support/CFG.h.orig	2012-02-17 18:59:53.000000000 +0000
+++ include/llvm/Support/CFG.h
@@ -27,8 +27,9 @@ namespace llvm {
 
 template <class Ptr, class USE_iterator> // Predecessor Iterator
 class PredIterator : public std::iterator<std::forward_iterator_tag,
-                                          Ptr, ptrdiff_t> {
-  typedef std::iterator<std::forward_iterator_tag, Ptr, ptrdiff_t> super;
+                                          Ptr, ptrdiff_t, Ptr*, Ptr*> {
+  typedef std::iterator<std::forward_iterator_tag, Ptr, ptrdiff_t, Ptr*,
+                                                                    Ptr*> super;
   typedef PredIterator<Ptr, USE_iterator> Self;
   USE_iterator It;
 
@@ -40,6 +41,7 @@ class PredIterator : public std::iterato
 
 public:
   typedef typename super::pointer pointer;
+  typedef typename super::reference reference;
 
   PredIterator() {}
   explicit inline PredIterator(Ptr *bb) : It(bb->use_begin()) {
@@ -50,7 +52,7 @@ public:
   inline bool operator==(const Self& x) const { return It == x.It; }
   inline bool operator!=(const Self& x) const { return !operator==(x); }
 
-  inline pointer operator*() const {
+  inline reference operator*() const {
     assert(!It.atEnd() && "pred_iterator out of range!");
     return cast<TerminatorInst>(*It)->getParent();
   }
@@ -100,10 +102,11 @@ inline const_pred_iterator pred_end(cons
 
 template <class Term_, class BB_>           // Successor Iterator
 class SuccIterator : public std::iterator<std::bidirectional_iterator_tag,
-                                          BB_, ptrdiff_t> {
+                                          BB_, ptrdiff_t, BB_*, BB_*> {
   const Term_ Term;
   unsigned idx;
-  typedef std::iterator<std::bidirectional_iterator_tag, BB_, ptrdiff_t> super;
+  typedef std::iterator<std::bidirectional_iterator_tag, BB_, ptrdiff_t, BB_*,
+                                                                    BB_*> super;
   typedef SuccIterator<Term_, BB_> Self;
 
   inline bool index_is_valid(int idx) {
@@ -112,6 +115,7 @@ class SuccIterator : public std::iterato
 
 public:
   typedef typename super::pointer pointer;
+  typedef typename super::reference reference;
   // TODO: This can be random access iterator, only operator[] missing.
 
   explicit inline SuccIterator(Term_ T) : Term(T), idx(0) {// begin iterator
@@ -142,7 +146,7 @@ public:
   inline bool operator==(const Self& x) const { return idx == x.idx; }
   inline bool operator!=(const Self& x) const { return !operator==(x); }
 
-  inline pointer operator*() const { return Term->getSuccessor(idx); }
+  inline reference operator*() const { return Term->getSuccessor(idx); }
   inline pointer operator->() const { return operator*(); }
 
   inline Self& operator++() { ++idx; return *this; } // Preincrement
