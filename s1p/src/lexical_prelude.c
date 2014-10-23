#include <smop/base.h>
#include <smop/s1p.h>
#include <smop/capture.h>
#include <stdlib.h>
#include <smop/s0native.h>
#include <stdio.h>
static SMOP__Object* SMOP__ID__new;
void smop_s1p_lexical_prelude_insert(SMOP__Object* interpreter,char* name,SMOP__Object* obj) {
  smop_lexical_scope_bind(interpreter,SMOP__S1P__LexicalPrelude,SMOP__NATIVE__idconst_create(name),obj);
}
void smop_s1p_lexical_prelude_init(SMOP__Object* interpreter) {
  SMOP__S1P__LexicalPrelude = SMOP_DISPATCH(
    interpreter,
    SMOP_RI(SMOP__S1P__LexicalScope),
    SMOP__NATIVE__idconst_create("new"),
    SMOP__NATIVE__capture_create(interpreter,(SMOP__Object*[]) {SMOP_REFERENCE(interpreter,SMOP__S1P__LexicalScope),NULL},(SMOP__Object*[]) {NULL})
  );
  SMOP__ID__new = SMOP__NATIVE__idconst_create("new");
  smop_s1p_lexical_prelude_insert(interpreter,"Code",SMOP_REFERENCE(interpreter,SMOP__S1P__Code));

  smop_s1p_lexical_prelude_insert(interpreter,"False",SMOP__NATIVE__bool_false);
  smop_s1p_lexical_prelude_insert(interpreter,"True",SMOP__NATIVE__bool_true);

  smop_s1p_lexical_prelude_insert(interpreter,"capture",SMOP__Proto__create(SMOP__capture__RI));
  smop_s1p_lexical_prelude_insert(interpreter,"$OUT",SMOP__S1P__IO_create(interpreter));
  smop_s1p_lexical_prelude_insert(interpreter,"MildewSOLoader",SMOP_REFERENCE(interpreter,SMOP__MildewSOLoader));
  smop_s1p_lexical_prelude_insert(interpreter,"$LexicalPrelude",SMOP_REFERENCE(interpreter,SMOP__S1P__LexicalPrelude));
  smop_s1p_lexical_prelude_insert(interpreter,"AdhocSignature",SMOP_REFERENCE(interpreter,SMOP__S1P__AdhocSignature));
  smop_s1p_lexical_prelude_insert(interpreter,"LexicalScope",SMOP_REFERENCE(interpreter,SMOP__S1P__LexicalScope));
  smop_s1p_lexical_prelude_insert(interpreter,"ControlExceptionReturn",
                                  SMOP_REFERENCE(interpreter,SMOP__ControlExceptionReturn));
  smop_s1p_lexical_prelude_insert(interpreter,"Scalar",SMOP_REFERENCE(interpreter,SMOP__S1P__Scalar));
  smop_s1p_lexical_prelude_insert(interpreter,"Hash",SMOP__S1P__Hash_create(interpreter));
  smop_s1p_lexical_prelude_insert(interpreter,"Package",SMOP_REFERENCE(interpreter,SMOP__S1P__Package));
  smop_s1p_lexical_prelude_insert(interpreter,"Array",SMOP_REFERENCE(interpreter,SMOP__S1P__Array));
  smop_s1p_lexical_prelude_insert(interpreter,"$?PACKAGE",
    SMOP_DISPATCH(interpreter,SMOP_RI(SMOP__S1P__Package),SMOP__ID__new,
    SMOP__NATIVE__capture_create(interpreter,
      (SMOP__Object*[]){
        SMOP_REFERENCE(interpreter,SMOP__S1P__Package),NULL},
      (SMOP__Object*[]) {NULL}
    )));

  SMOP__Object* primitives = SMOP_DISPATCH(interpreter,SMOP_RI(SMOP__S1P__Package),SMOP__ID__new,
    SMOP__NATIVE__capture_create(interpreter,
    (SMOP__Object*[]) {SMOP_REFERENCE(interpreter,SMOP__S1P__Package),NULL},(SMOP__Object*[]) {NULL}));

  smop_s1p_insert_primitives(interpreter,primitives);
  smop_s1p_lexical_prelude_insert(interpreter,"PRIMITIVES::",primitives);
}

void smop_s1p_lexical_prelude_destr(SMOP__Object* interpreter) {
  smop_s1p_lexical_prelude_insert(interpreter,"$LexicalPrelude",SMOP__NATIVE__bool_false);
  SMOP_RELEASE(interpreter,SMOP__S1P__LexicalPrelude);
}
