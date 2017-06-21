! ===========================================================================
!   Inform Language Definition File: Swedish 20040310
!   Derived from English.h dated 000629. Updated to be compatible with
!   English.h dated 040227
!
!   Supplied for use with Inform 6 -- Release 6/11 -- Serial number 040227
!
!   Copyright Graham Nelson 1993-2004 but freely usable (see manuals)
!   Translation (c) Fredrik Ramsberg 2003-2004
!
!   This translation has a license which should always be distributed
!   along with it. It basically says that you're free to use the translation,
!   as long as you don't sell it and don't claim that you've written it.
!   You may sell games compiled using this translation though.
!
!   This file is automatically Included in your game file by "parserm".
!   Strictly, "parserm" includes the file named in the "language__" variable,
!   whose contents can be defined by +language_name=XXX compiler setting (with 
!   a default of "english").
!
! ---------------------------------------------------------------------------

System_file;

! Konventioner i k�llkoden:
! *#* betyder kvarvarande problem
! �#� betyder �tg�rdat problem

#ifndef LIBRARY_VERSION;
  Message "Warning: This version of Swedish.h was made for use with library 6/11.";
#endif;
#iftrue LIBRARY_VERSION < 611;
  Message "Warning: This version of Swedish.h was made for use with library 6/11.";
#endif;

! ---------------------------------------------------------------------------
!   First we need to replace some routines
! ---------------------------------------------------------------------------

! Routines in Parserm.h, to be replaced by routines in SweRout.h
Replace ResetDescriptors;
Replace Descriptors;
Replace ScoreMatchL;
Replace PrintCommand;
Replace CantSee;
Replace GetGNAOfObject;
Replace PronounNotice;
Replace PrefaceByArticle;

Replace Indefart;
Replace CInDefart;
Replace Defart;
Replace CDefart;

! Routines in Verblibm.h, to be replaced by routines in SweRout.h

Replace WriteAfterEntry;
Replace Objects1Sub;



! ---------------------------------------------------------------------------
!   Part I.   Preliminaries
! ---------------------------------------------------------------------------

Constant LanguageVersion = "�vers�ttning av biblioteket till svenska (c) Fredrik Ramsberg 2003-2004";

Global caps_mode;
Global transcribe_mode;

Attribute def_article;
Attribute uter;

Property short_name_def;

[ PrintString the_array   i last;
    last=WORDSIZE + the_array-->0;
    for (i=WORDSIZE: i<last: i++)
       print (char) the_array->i;
];

[check_caps obj   c k;
  c = k;
  if(metaclass(obj)==String)
    print (string) obj;
  else
    print (object) obj;
  rtrue;
];

[ zcheck_caps obj     c k; ! Has to accept at least two params, second param
                          ! value being either print_object_flag or ignored, 
                          ! for backwards compatibility
  if(caps_mode) {
    caps_mode=0;
    PrintToBuffer(StorageForShortName, 160, obj);
    k=StorageForShortName-->0;
    ! �#� Must first check if first character is actually shiftable, and check for accented characters
    if(k>0) {
      c=StorageForShortName->WORDSIZE;
      c=UpperCase(c);
      StorageForShortName->WORDSIZE=c;
      PrintString(StorageForShortName);
    }
  } else if(metaclass(obj)==String)
    print (string) obj;
  else
    print (object) obj;
  rtrue;
];


#ifdef DEBUG;
[CheckGameSub i j err anyerr isnormalobj;
  style bold;
  print  "Kollar efter f�ljande (m�jliga) problem:^* Saknar b�de short_name_def och short_name.
    ^* Har short_name OCH short_name_indef eller short_name_def.^^";
  style roman;
  anyerr=false;
  objectloop(i>LibraryMessages && ~~(i ofclass class)) {
    err=false;
    isnormalobj=parent(i)~=0 || i hasnt light;
    if(isnormalobj && parent(i)==0) { ! Check if dark, lonely objects have exits
      objectloop(j in compass) isnormalobj=isnormalobj && (i.(j.door_dir)==0);
    }
    if(i.short_name_def==0 && i.short_name==0 && i hasnt proper && isnormalobj) {
      err=true;
      print "Saknar b�de short_name_def och short_name";
    } else if(i.short_name~=0 && (i.short_name_def~=0 || i.short_name_indef~=0)) {
      err=true;
      print "Har short_name OCH short_name_indef eller short_name_def";
    }
    if(err) {
      print ": ",(name) i, ".^";
      anyerr=true;
    }
  }
  if(~~anyerr) "Inga problem hittades.";
];
#endif;

[SetGender x gender;
  if(x has male or female or uter or neuter) rtrue;
  if(x has animate) gender = LanguageAnimateGender;
  else gender = LanguageInanimateGender;
  switch(gender) {
    male: give x male;
    female: give x female;
    uter: give x uter;
    neuter: give x neuter;
  }
];

Class   CompassDirection
  with  number 0,
        description [;
            if (location provides compass_look && location.compass_look(self)) rtrue;
            if (self.compass_look()) rtrue;
            L__M(##Look, 7, self);
        ],
        compass_look false,
  has   scenery proper;
Object Compass "compass" has concealed;
IFNDEF WITHOUT_DIRECTIONS;
CompassDirection -> n_obj "norr"
                    with door_dir n_to, name 'n//' 'norra' 'norr' 'norrut' 'norr�ver' 'nord';
CompassDirection -> s_obj "s�der"
                    with door_dir s_to, name 's//' 's�dra' 's�der' 's�derut' 's�der�ver' 'syd';
CompassDirection -> e_obj "�ster"
                    with door_dir e_to, name '�//' '�stra' '�ster' '�sterut' '�st' '�st�ver' '�ster�ver' 'o//';
CompassDirection -> w_obj "v�ster"
                    with door_dir w_to, name 'v//' 'v�stra' 'v�ster' 'v�sterut' 'v�st' 'v�st�ver' 'v�ster�ver';
CompassDirection -> ne_obj "nordost"
                    with door_dir ne_to, name 'n�' 'no' 'nord�stra' 'nord�ster' 'nord�st' 'nordost';
CompassDirection -> nw_obj "nordv�st"
                    with door_dir nw_to, name 'nv' 'nordv�stra' 'nordv�ster' 'nordv�st';
CompassDirection -> se_obj "sydost"
                    with door_dir se_to, name 's�' 'so' 'syd�stra' 'syd�ster' 'syd�st' 'sydost';
CompassDirection -> sw_obj "sydv�st"
                    with door_dir sw_to, name 'sv' 'sydv�stra' 'sydv�ster' 'sydv�st';
CompassDirection -> u_obj "upp"
                    with door_dir u_to, name 'u//' 'upp' 'upp�t' 'tak' 'taket' 'himlen' 'skyn';
CompassDirection -> d_obj "marken"
                    with door_dir d_to, name 'ner' 'ner�t' 'golv' 'golvet' 'mark' 'marken' 'ned' 'ned�t';
ENDIF;
CompassDirection -> in_obj "insidan"
                    with door_dir in_to;
CompassDirection -> out_obj "utsidan"
                    with door_dir out_to, name 'ut';
! ---------------------------------------------------------------------------
!   Part II.   Vocabulary
! ---------------------------------------------------------------------------
Constant AGAIN1__WD   = 'igen';
Constant AGAIN2__WD   = 'g//';
Constant AGAIN3__WD   = 'igen';
Constant OOPS1__WD    = 'oj';
Constant OOPS2__WD    = 'ojd�';
Constant OOPS3__WD    = 'ojsan';
Constant UNDO1__WD    = 'og�r';
Constant UNDO2__WD    = '�ngra';
Constant UNDO3__WD    = '�ngra';

Constant ALL1__WD     = 'alla';
Constant ALL2__WD     = 'varje';
Constant ALL3__WD     = 'allihop';
Constant ALL4__WD     = 'samtliga';
Constant ALL5__WD     = 'allt';
Constant AND1__WD     = 'och';
Constant AND2__WD     = 'samt';
Constant AND3__WD     = '�ven';
Constant BUT1__WD     = 'utom';
Constant BUT2__WD     = 'f�rutom';
Constant BUT3__WD     = 'utom';
Constant ME1__WD      = 'jag';
Constant ME2__WD      = 'mig';
Constant ME3__WD      = 'sj�lv';
Constant OF1__WD      = 'av';
Constant OF2__WD      = 'bland';
Constant OF3__WD      = 'utav';
Constant OF4__WD      = 'av';
Constant OTHER1__WD   = 'andra';
Constant OTHER2__WD   = 'andre';
Constant OTHER3__WD   = 'annan';
Constant THEN1__WD    = 'och,';
Constant THEN2__WD    = 'och,';
Constant THEN3__WD    = 'och,';

Constant NO1__WD      = 'n//';
Constant NO2__WD      = 'nej';
Constant NO3__WD      = 'n�';
Constant YES1__WD     = 'j//';
Constant YES2__WD     = 'ja';
Constant YES3__WD     = 'jo';

Constant AMUSING__WD  = 'roliga';
Constant FULLSCORE1__WD = 'fullpo�ng';
Constant FULLSCORE2__WD = 'full';
Constant QUIT1__WD    = 'avsluta';
Constant QUIT2__WD    = 'sluta';
Constant RESTART__WD  = 'b�rja';
Constant RESTORE__WD  = 'h�mta';

! �#� The need for uter, in addition to male, female and neuter,
! necessitates the adding of four bits to every GNA-word. While
! there was indeed room for these bits, it still implies that
! one or more of the other library files will have to be modified
! as well to interpret these words correctly in order to handle
! the four genders correctly.

Array LanguagePronouns table ! �#� Usage of this array must be modified to add uter

   !  word       possible GNAs                   connected
   !             to follow:                      to:
   !             a       i
   !             s   p   s   p
   !             mfunmfunmfunmfun

      'honom'  $$1000000010000000                NULL
      'henne'  $$0100000001000000                NULL
      'den'    $$0010000000100000                NULL
      'det'    $$0001000000010000                NULL
      'dem'    $$0000111100001111                NULL;
!      'dom'    $$0000111100001111                NULL; !�#� Decided to leave this out because it gets ugly when player types "pronomen" (pronouns)

Array LanguageDescriptors table ! �#� Usage of this array must be modified to add uter

   !  word       possible GNAs    descriptor     connected
   !             to follow:       type:          to:
   !             a       i
   !             s   p   s   p
   !             mfunmfunmfunmfun

      'min'    $$1110000011100000 POSSESS_PK      0
      'mitt'   $$0001000000010000 POSSESS_PK      0
      'mina'   $$0000111100001111 POSSESS_PK      0
! *#* Hard to translate and not very important, skipping
!      'this'   $$111111111111    POSSESS_PK      0
!      'these'  $$000111000111    POSSESS_PK      0
!      'that'   $$111111111111    POSSESS_PK      1
!      'those'  $$000111000111    POSSESS_PK      1
      'hans'   $$1111111111111111 POSSESS_PK      'honom'
      'hennes' $$1111111111111111 POSSESS_PK      'henne'
      'deras'  $$1111111111111111 POSSESS_PK      'dem'
      'dess'   $$1111111111111111 POSSESS_PK      'den' ! *#* Not quite correct, it may also refer to "det"
      'den'    $$1110000011100000 DEFART_PK       NULL ! �#� These have been commented out because their usage
      'det'    $$0001000000010000 DEFART_PK       NULL !     as definite articles conflict with their usage as
      'de'     $$0000111100001111 DEFART_PK       NULL !     it-words. Should be corrected in the parser somehow.
      'en'     $$1110000011100000 INDEFART_PK     NULL
      'ett'    $$0001000000010000 INDEFART_PK     NULL
      'n�gra'  $$0000111100001111 INDEFART_PK     NULL
      't�nd'   $$1110000011100000 light           NULL
      't�nt'   $$0001000000010000 light           NULL
      't�nda'  $$1111111111111111 light           NULL
      't�nde'  $$1000000010000000 light           NULL
      'sl�ckt' $$1111000011110000 (-light)        NULL
     'sl�ckte' $$1000000010000000 (-light)        NULL
     'sl�ckta' $$1111111111111111 (-light)        NULL;

Array LanguageNumbers table
    'en' 1 'ett' 1 'tv�' 2 'tvenne' 2 'tre' 3 'trenne' 3 'fyra' 4 'fem' 5
    'sex' 6 'sju' 7 '�tta' 8 'nio' 9 'tio' 10
    'elva' 11 'tolv' 12 'tretton' 13 'fjorton' 14 'femton' 15
    'sexton' 16 'sjutton' 17 'arton' 18 'aderton' 18 'nitton' 19 'tjugo' 20;

! ---------------------------------------------------------------------------
!   Part III.   Translation
! ---------------------------------------------------------------------------

[LTI_delete pos n   k m;
!  print pos,",", n, ".";
  if(n<1) n=1;
#ifdef TARGET_ZCODE;
  m=(buffer->1)+3-n;
#ifnot; ! TARGET_GLULX
  m=(buffer-->0)+5-n;
#endif; ! TARGET_
  for(k=pos:k<m:k++)
    buffer->k=buffer->(k+n);
#ifdef TARGET_ZCODE;
  buffer->1=(buffer->1)-n;
#ifnot; ! TARGET_GLULX
  buffer-->0=(buffer-->0)-n;
#endif; ! TARGET_
];

! *#* One could definitely do a lot more work here...

[ LanguageToInformese   i c1 c2 cnew no_transcribe changed;

! This section handles transciption of aa, ae and oe into �, � and � respectively

#ifdef TARGET_ZCODE;
  if(transcribe_mode && buffer->1>1) {
    for(i=2:i<1+buffer->1:i++) { ! Stop one character before the last
#ifnot; ! TARGET_GLULX
  if(transcribe_mode && buffer-->0>1) {
    for(i=4:i<3+buffer-->0:i++) { ! Stop one character before the last
#endif; ! TARGET_
!      print "#";
      c1=buffer->i;
      c2=buffer->(i+1);
      if(c1=='!') {
        no_transcribe++;
        LTI_delete(i);
        i--;
        changed=1;
        continue;
      }  
      if(c1=='a') {
        if(c2=='a')
          cnew='�';
        if(c2=='e')
          cnew='�';
      }
      if(c1=='o' && c2=='e')
        cnew='�';
      if(cnew) {
        if(no_transcribe)
          no_transcribe--;
        else {
          buffer->i=cnew;
          LTI_delete(i+1);
          changed=1;
        }
        cnew=0;
      }
    }
    if(changed)
      Tokenise__(buffer,parse);
    if(transcribe_mode>1 && changed) {
      print "(transkriberades till ~";
#ifdef TARGET_ZCODE;
      for(i=2:i<2+buffer->1:i++) print (char) buffer->i;
#ifnot; ! TARGET_GLULX
      for(i=4:i<4+buffer-->0:i++) print (char) buffer->i;
#endif; ! TARGET_
      print "~)"; 
      new_line;
    }

  }

! This section changes "mig sj�lv" to "mig", to avoid a pronoun consisting of two words

#ifdef TARGET_ZCODE;
  for(i=2:i<=parse->1:i++)
    if(parse-->(2*i-1)=='sj�lv' && parse-->(2*i-3)=='mig' or 'mej') {
      LTI_delete((parse->(4*i+1))-1,(parse->(4*i))+1);
      Tokenise__(buffer,parse);
    }
#ifnot; ! TARGET_GLULX
  for(i=2:i<=parse-->0:i++)
    if(parse-->(3*i-2)=='sj�lv' && parse-->(3*i-5)=='mig' or 'mej') {
      LTI_delete((parse-->(3*i))-1,(parse-->(3*i-1))+1);
      Tokenise__(buffer,parse);
    }
#endif; ! TARGET_

];

[ TranscribeOnSub;
  if(transcribe_mode==0 or 2)
    L__M(##TranscribeOn,2);
  else
    L__M(##TranscribeOn,1);
  transcribe_mode=1;
];

[ TranscribeShowSub;
  if(transcribe_mode==0 or 1)
    L__M(##TranscribeShow,2);
  else
    L__M(##TranscribeShow,1);
  transcribe_mode=2;
];

[ TranscribeOffSub;
  if(transcribe_mode>0)
    L__M(##TranscribeOff,2);
  else
    L__M(##TranscribeOff,1);
  transcribe_mode=0;
];
  

! ---------------------------------------------------------------------------
!   Part IV.   Printing
! ---------------------------------------------------------------------------

Constant LanguageAnimateGender   = male;
Constant LanguageInanimateGender = uter;

Constant LanguageContractionForms = 1;     ! Swedish has only 1:
                                           ! 0 = no matter what

[ LanguageContraction text x;
  x=text; ! �#� Only here to avoid a warning
  return 0;
];

Array LanguageArticles -->

 !   Contraction form 0:
 !   Cdef   Def    Indef

! �#� Cdef and Def should not be printed unless there is an adjective before the noun

     "Den " "den " "en "        ! masc/fem/uter sing
     "Det " "det " "ett "       ! neuter sing
     "De "  "de "  "n�gra ";    ! plural

                   !             a               i
                   !             s       p       s       p
                   !             m f u n m f u n m f u n m f u n

Array LanguageGNAsToArticles --> 0 0 0 1 2 2 2 2 0 0 0 1 2 2 2 2; ! �#� Usage of this array must be modified to add uter

[LanguagePrintShortName o  i;
  if(indef_mode==false)
    i=short_name_def;
  else
    i=short_name_indef;
   if(o.&i~=0) {
     if(metaclass(o.i)==String) {
       print (string) o.i;
       rtrue;
     }
     else if(metaclass(o.i)==Routine) {
       if(PrintOrRun(o, i)==true)
         rtrue;
     } else
       rtrue; ! Incorrect type of value
   }
   if(o.&short_name~=0) {
     if(metaclass(o.short_name)==String) {
       print (string) o.short_name;
       rtrue;
     }  
     else if(metaclass(o.short_name)==Routine) {
       if(PrintOrRun(o, short_name)==true)
         rtrue;
     } else
       rtrue; ! Incorrect type of value
   }
  print (object) o;
  rtrue;
];

[ LanguageDirection d;
   switch(d)
   {   n_to: print "norrut";
       s_to: print "s�derut";
       e_to: print "�sterut";
       w_to: print "v�sterut";
       ne_to: print "nordost";
       nw_to: print "nordv�st";
       se_to: print "sydost";
       sw_to: print "sydv�st";
       u_to: print "upp�t";
       d_to: print "ner�t";
       in_to: print "in";
       out_to: print "ut";
       default: return RunTimeError(9,d);
   }
];

Constant ENDS_WITH_T = 2;

[ LanguageNumber n force_neuter_1 obj gender f;
  if(obj~=0 && metaclass(obj)==Object) {
    if(obj has neuter) gender=neuter;
    else gender=uter;
  }
  if((gender==neuter || force_neuter_1~=0) && n==1) { print "ett"; return ENDS_WITH_T;}
  if (n==0)    { print "noll"; rfalse; }
  if (n<0)     { print "minus "; n=-n; }
  if (n>=1000) {
    if(LanguageNumber(n/1000, force_neuter_1, false, neuter)~=ENDS_WITH_T)
      print "t";
    print "usen";
    n=n%1000;
    f=1;
  }
  if (n>=100)  { LanguageNumber(n/100, force_neuter_1, false, neuter); print "hundra"; n=n%100; f=1; }
  if (n==0) rfalse;
  switch(n)
  {   1:  if(force_neuter_1) { print "ett"; return ENDS_WITH_T; } else print "en"; ! �#� This could also be "ett", if printing how many objects of a certain kind there are, and the objects are neuter
      2:  print "tv�";
      3:  print "tre";
      4:  print "fyra";
      5:  print "fem";
      6:  print "sex";
      7:  print "sju";
      8:  print "�tta";
      9:  print "nio";
      10: print "tio";
      11: print "elva";
      12: print "tolv";
      13: print "tretton";
      14: print "fjorton";
      15: print "femton";
      16: print "sexton";
      17: print "sjutton";
      18: print "arton";
      19: print "nitton";
      20 to 99:
          switch(n/10)
          {  2: print "tjugo";
             3: print "trettio";
             4: print "fyrtio";
             5: print "femtio";
             6: print "sextio";
             7: print "sjuttio";
             8: print "�ttio";
             9: print "nittio";
          }
          if (n%10 ~= 0) return LanguageNumber(n%10, force_neuter_1);
  }
];

[ LanguageTimeOfDay hours mins;
   print hours/10, hours%10, ":", mins/10, mins%10;
];

[ LanguageVerb i;
    switch (i) {
      'l//',
      'lista': print "lista dina tillh�righeter";
      't//':   print "titta";
      'x//':   print "unders�k";
      'z//':   print "v�nta";
      'inspelning':     print "inspelning";
      'meddelanden':    print "meddelanden";
      'substantiv':     print "substantiv";
      'transkribera':   print "transkribera";
      'transkription':  print "transkription";
      'uppspelning':    print "uppspelning";
      'dubbeltusan':    print "dubbeltusan";
      'j�rnspikar':     print "j�rnspikar";
      default: rfalse;
    }
    rtrue;
];

! ----------------------------------------------------------------------------
!  LanguageVerbIsDebugging is called by SearchScope.  It should return true 
!  if word w is a debugging verb which needs all objects to be in scope.
! ----------------------------------------------------------------------------

#Ifdef DEBUG;
[ LanguageVerbIsDebugging w;
    if (w == 'purloin' or 'tree' or 'abstract'
                       or 'gonear' or 'scope' or 'showobj')
        rtrue;
    rfalse;
];
#Endif;

! ----------------------------------------------------------------------------
!  LanguageVerbLikesAdverb is called by PrintCommand when printing an UPTO_PE
!  error or an inference message.  Words which are intransitive verbs, i.e.,
!  which require a direction name as an adverb ('walk west'), not a noun
!  ('I only understood you as far as wanting to touch /the/ ground'), should
!  cause the routine to return true.
! ----------------------------------------------------------------------------

[ LanguageVerbLikesAdverb w;
    if (w == 'titta' or 'g�' or 'spring' or 'flytta' or 'tryck' or 'knuffa' 
          or 'putta')
        rtrue;
    rfalse;
];

! ----------------------------------------------------------------------------
!  LanguageVerbMayBeName is called by NounDomain when dealing with the 
!  player's reply to a "Which do you mean, the short stick or the long
!  stick?" prompt from the parser. If the reply is another verb (for example,
!  LOOK) then then previous ambiguous command is discarded /unless/
!  it is one of these words which could be both a verb /and/ an
!  adjective in a 'name' property.
! ----------------------------------------------------------------------------

[ LanguageVerbMayBeName w;
    if (w == 'full' or 'l�ng' or 'l�ngt' or 'l�nga' or 'normalt' or 'normal'
          or 'normala' or 'kort' or 'korta' or 'visa' or '�ppna' or 'vakna'
          or 't�nd')
        rtrue;
    rfalse;
];


Constant NKEY__TX     = "N=n�sta �mne";
Constant PKEY__TX     = "F=f�reg�ende";
Constant QKEY1__TX    = "X=�ter till spelet";
Constant QKEY2__TX    = "X=f�reg�ende meny";
Constant RKEY__TX     = "RETURN=l�s �mne";

Constant NKEY1__KY    = 'N';
Constant NKEY2__KY    = 'n';
Constant PKEY1__KY    = 'F';
Constant PKEY2__KY    = 'f';
Constant QKEY1__KY    = 'X';
Constant QKEY2__KY    = 'x';

Constant SCORE__TX    = "Po�ng: ";
Constant MOVES__TX    = "Drag: ";
Constant TIME__TX     = "Tid: ";
Constant CANTGO__TX   = "Du kan inte g� d�r�t.";
Constant FORMER__TX   = "ditt tidigare jag";
Constant YOURSELF__TX = "dig sj�lv";
Constant YOU__TX      = "Du";
Constant DARKNESS__TX = "M�rker";

Constant THOSET__TX   = "dem";
Constant THAT__TX     = "den"; ! �#� Should this be "det" in case we're talking about something neuter?
Constant OR__TX       = " eller ";
Constant NOTHING__TX  = "ingenting";
Constant IS__TX       = " �r";
Constant ARE__TX      = " �r";
Constant IS2__TX      = "�r ";
Constant ARE2__TX     = "�r ";
Constant AND__TX      = " och ";
Constant WHOM__TX     = "vilken ";
Constant WHICH__TX    = "vilken ";
Constant COMMA__TX      = ", ";

[ GetSecondaryGNAOfObject obj case gender;
   if (obj hasnt animate) case = 8;

   if (obj has uter) gender = uter;
   if (obj has neuter) gender = neuter;
   if (obj has female) gender = female;
   if (obj has male) gender = male;

   if (gender == 0)
   {   if (case == 0) gender = LanguageAnimateGender;
       else gender = LanguageInanimateGender;
   }
   if (gender == female) case = case + 1;

   if (gender == uter) case = case + 2;
   if (gender == neuter) case = case + 3;
   if (obj has pluralname) case = case + 4;
   return case;
];

[ DenEllerHan obj;   ! Used in the nominative
  SetGender(obj);
  if (obj == player) { print "du"; return; }
  if (obj has pluralname) { print "de"; return; }
  if (obj has uter) { print "den"; return; }
  if (obj has neuter) { print "det"; return; } ! �#� This must be modified to cover uter as well!
  if (obj has female) { print "hon"; return; }
  print "han";
];
[ CDenEllerHan obj;   ! Used in the accusative
  SetGender(obj);
  if (obj == player) { print "Du"; return; }
  if (obj has pluralname) { print "De"; return; }
  if (obj has uter) { print "Den"; return; }
  if (obj has neuter) { print "Det"; return; } ! �#� This must be modified to cover uter as well!
  if (obj has female) { print "Hon"; return; }
  print "Han";
];
[ DenEllerHonom obj;   ! Used in the accusative
  SetGender(obj);
  if (obj == player) { print "dig sj�lv"; return; }
  if (obj has pluralname) { print "dem"; return; }
  if (obj has uter) { print "den"; return; }
  if (obj has neuter) { print "det"; return; } ! �#� This must be modified to cover uter as well!
  if (obj has female) { print "henne"; return; }
  print "honom";
];
[ CDenEllerHonom obj;   ! Used in the accusative
  SetGender(obj);
  if (obj == player) { print "Dig sj�lv"; return; }
  if (obj has pluralname) { print "Dem"; return; }
  if (obj has uter) { print "Den"; return; }
  if (obj has neuter) { print "Det"; return; } ! �#� This must be modified to cover uter as well!
  if (obj has female) { print "Henne"; return; }
  print "Honom";
];

[ IndefAdjOpen obj;
  if (obj hasnt pluralname) {
    if (obj has neuter) { print "�ppet"; return; }
    print "�ppen"; return;
  }
  print "�ppna";
];
[ IndefAdjClosed obj;
  if (obj hasnt pluralname) {
    if (obj has neuter) { print "st�ngt"; return; }
    print "st�ngd"; return;
  }
  print "st�ngda";
];
[ IndefAdjEmpty obj;
  if (obj hasnt pluralname) {
    if (obj has neuter) { print "tomt"; return; }
    print "tom"; return;
  }
  print "tomma";
];
[ IndefAdjWorn obj;
  if (obj hasnt pluralname) {
    if (obj has neuter) { print "p�taget"; return; }
    print "p�tagen"; return;
  }
  print "p�tagna";
];
[ IndefAdjLocked obj;
  if (obj hasnt pluralname) { print "l�st"; return; }
  print "l�sta";
];
[ IndefAdjHeld obj;
  if (obj hasnt pluralname) {
    if (obj has neuter) { print "buret"; return; }
    print "buren"; return;
  }
  print "burna";
];
[ IndefAdjGiven obj;
  if (obj hasnt pluralname) {
    if (obj has neuter) { print "bortgivet"; return; }
    print "bortgiven"; return;
  }
  print "bortgivna";
];


[ WhichorWhom obj;
  if (obj has pluralname) {print "vilka"; return; }
  if (obj has neuter) {print "vilket"; return; }
  print "vilken";
];

[ LanguageLM n x1;
  Prompt:  print "^>";

  Answer, Ask:    "Du f�r inget svar.";
  Attack:         "V�ld �r knappast l�sningen h�r.";
  Blow:           "Det vore meningsl�st att bl�sa p� ", (DenEllerHonom) x1, ".";
  Burn:           "Det vore farligt och f�ga produktivt.";
  Buy:            "Det finns just inget att k�pa.";
  Climb:          "Det verkar inte s� konstruktivt.";
  Close:   switch(n)
           {   1: print_ret (CDenEllerHan) x1,"  �r inte n�got du kan st�nga.";
               2: print_ret (CDenEllerHan) x1,
                  " �r redan ",(indefadjclosed) x1,".";
               3: "Du st�nger ", (the) x1, ".";
           }
  CommandsOff: switch (n) {
        1: "[Kommandoinspelning avslutad.]";
        #Ifdef TARGET_GLULX;
        2: "[Kommandoinspelning var redan avslagen.]";
        #Endif; ! TARGET_
    }
  CommandsOn: switch (n) {
        1: "[Kommandoinspelning startad.]";
        #Ifdef TARGET_GLULX;
        2: "[Kommandon spelas just nu upp.]";
        3: "[Kommandoinspelning var redan p�slagen.]";
        4: "[Kommandoinspelning misslyckades.]";
        #Endif; ! TARGET_
    }
  CommandsRead: switch (n) {
        1: "[Spelar upp kommandon.]";
        #Ifdef TARGET_GLULX;
        2: "[Kommandon h�ller redan p� att spelas upp.]";
        3: "[Uppspelning av kommandon misslyckades. Kommandoinspelning p�g�r.]";
        4: "[Uppspelning av kommandon misslyckades.]";
        5: "[Uppspelning av kommandon avlsutad.]";
        #Endif; ! TARGET_
    }
  Consult:        "Du uppt�cker inget intressant i ", (the) x1, ".";
  Cut:            "Att sk�ra i ", (DenEllerHonom) x1, " verkar inte s�rskilt konstruktivt.";
  Dig:            "Det kan inte ge s� mycket att gr�va h�r.";
  Disrobe: switch(n)
           {   1: print_ret (CDenEllerHonom) x1, " har du inte p� dig.";
               2: "Du tar av ", (the) x1, ".";
           }
  Drink:          "Det finns inget v�rt att dricka h�r.";
  Drop:    switch(n)
           {   1: print_ret (CDenEllerHan) x1, " �r redan h�r.";
               2: "Du har inte ", (DenEllerHonom) x1, ".";
               3: "(tar f�rst av ", (the) x1, ")";
               4: "Sl�ppt.";
           }
  Eat:     switch(n)
           {   1: print (CDenEllerHan) x1," �r helt enkelt o�tlig";
                  if(x1 has pluralname) "a.";
                  if(x1 has neuter) "t."; else ".";
               2: "Du �ter ", (the) x1, ". Inte illa.";
           }
  EmptyT:  switch(n)
           {   1: print_ret (The) x1, " kan inte inneh�lla saker.";
               2: print_ret (The) x1, " �r ",(indefadjclosed) x1,".";
               3: print_ret (The) x1, " �r redan ",(indefadjempty) x1,".";
               4: "Det skulle just inte t�mma n�gonting alls.";
           }
  Enter:   switch(n)
           {   1: print "Men du �r ju redan ";
                  if (x1 has supporter) print "p� "; else print "i ";
                  print_ret (the) x1, ".";
               2: print (CDenEllerHan) x1, " �r inte till f�r "; ! �#� Should be more varied.
                  switch (verb_word) {
                      'st�','st�ll': "att st� p�.";
                      'sitt': "att sitta p�.";
                      'ligg': "att ligga p�.";
                      default: "det.";
                  }
               3: print_ret (The) x1, " �r ",(indefadjclosed) x1,", s� det blir nog sv�rt.";
               4: "F�rst m�ste du st� p� dina egna f�tter igen.";
               5: switch (verb_word) {
                      'st�','st�ll': print "Du st�ller dig";
                      'sitt','s�tt': print "Du s�tter dig";
                      'ligg','l�gg': print "Du l�gger dig";
                      default: print "Du kliver "; if(x1 has supporter) print "upp"; else print "in";
                  }
                  if (x1 has supporter) print " p� "; else print " i ";
                  print_ret (the) x1, ".";
               6: "(du l�mnar ",(the) x1, ")";
               7: if (x1 has supporter) "(kliver p� ", (the) x1, ")^";
                  if (x1 has container) "(kliver in i ", (the) x1, ")^";
                  "(g�r p� ", (the) x1, ")^";
           }
  Examine: switch(n)
           {   1: "M�rker, substantiv. En fr�nvaro av ljus att se i.";
               2: "Du ser inget speciellt med ", (the) x1, ".";
               3: print (The) x1, " �r just nu ";
                  if (x1 has on) "p�."; else "av.";
           }
  Exit:    switch(n)
           {   1: "Men du �r ju inte i n�got f�r tillf�llet.";
               2: "Det kan bli sv�rt, efterom ", (the) x1, " �r ",(indefadjclosed) x1,".";
               3: "Du l�mnar ",(the) x1, ".";
               4: print "Men du �r inte ";
                  if (x1 has supporter) print "p� "; else print "i ";
                  print_ret (the) x1, ".";
           }
  Fill:           "Men det finns inget vatten h�r att fylla p�.";
  FullScore: switch(n)
           {   1: if (deadflag) print "Du fick ";
                  else          print "Du har ";
                  "po�ng, f�rdelat enligt f�ljande:^";
               2: "hitta viktiga f�rem�l";
               3: "bes�ka viktiga platser";
               4: print "totalt (av ", MAX_SCORE; ")";
           }
  GetOff:         "Men du �r ju inte p� ", (the) x1, " f�r tillf�llet.";
  Give:    switch(n)
           {   1: "Du h�ller inte i ", (the) x1, ".";
               2: "Du bollar lite med ", (the) x1,
                  ", men det ger inte s� mycket.";
               3: print_ret (The) x1, " verkar inte bry sig om ditt erbjudande.";
           }
  Go:      switch(n)
           {   1: print "F�rst m�ste du kliva ";
                  if (x1 has supporter) print "av "; else print "ur ";
                  print_ret (the) x1, ".";
               2: print_ret (string) CANTGO__TX;   ! "You can't go that way."
               3: "Du kan inte kl�ttra upp p� ", (the) x1, ".";
               4: "Du kan inte kl�ttra ner p� ", (the) x1, ".";
               5: "Det blir sv�rt, eftersom ", (the) x1, " �r i v�gen.";
               6: "Det kan du inte, eftersom ", (the) x1," inte leder n�gonstans.";
           }
  Insert:  switch(n)
           {   1: "Du m�ste h�lla i ", (the) x1,
                  " innan du kan l�gga ", (DenEllerHonom) x1,
                  " i n�got annat.";
               2: print_ret (CDenEllerHan) x1, " kan inte inneh�lla saker.";
               3: print_ret (The) x1, " �r ",(indefadjclosed) x1,".";
               4: "F�rst m�ste du ta av ", (DenEllerHonom) x1, ".";
               5: "Du kan inte l�gga n�got i sig sj�lvt.";
               6: "(tar f�rst av ", (DenEllerHonom) x1, ")^";
               7: "Det finns inte plats f�r n�got mer i ", (the) x1, ".";
               8: "Gjort.";
               9: "Du placerar ", (the) x1, " i ", (the) second, ".";
           }
  Inv:     switch(n)
           {   1: "Du har ingenting.";
               2: print "Du har";
               3: print ":^";
               4: print ".^";
           }
  Jump:           "Du hoppar p� st�llet. Det ger inget.";
  JumpOver, Tie:  "Det skulle inte vara till n�gon st�rre hj�lp.";
  Kiss:           "T�nk lite mer p� spelet ist�llet.";
  Listen:         "Du h�r inget ov�ntat.";
  ListMiscellany:
           switch(n)
           {   1: print " (lyser)";
               2: print " (",(indefadjclosed) x1,")";
               3: print " (som �r ",(indefadjclosed) x1," och lyser)";
               4: print " (",(indefadjempty) x1,")";
               5: print " (som �r ",(indefadjempty) x1," och lyser)";
               6: print " (som �r ",(indefadjclosed) x1," och ",(indefadjempty) x1,")";
               7: print " (som �r ",(indefadjclosed) x1,", ",(indefadjempty) x1," och lyser)";
               8: print " (som lyser och �r ",(indefadjworn) x1;
               9: print " (lyser";
              10: print " (",(indefadjworn) x1;
              11: print " (som ";
              12: print "�r ", (indefadjopen) x1;
              13: print "�r ", (indefadjopen) x1," men ",(indefadjempty) x1;
              14: print "�r ", (indefadjclosed) x1;
              15: print "�r ", (indefadjclosed) x1," och ",(indefadjlocked) x1;
              16: print " och ",(indefadjempty) x1;
              17: print " (som �r ",(indefadjempty) x1,")";
              18: print " inneh�llande ";
              19: print " (p� ";
              20: print ", ovanp� ";
              21: print " (i ";
              22: print ", inuti ";
           }
  LMode1:         " �r nu i ~normalt~ utskriftsl�ge, vilket ger
                    l�nga beskrivningar av platser du aldrig varit p� tidigare
                    och annars korta beskrivningar.";
  LMode2:         " �r nu i ~l�ngt~ utskriftsl�ge, vilket alltid ger l�nga
                   beskrivningar av platser
                   (�ven om du har varit d�r f�rut).";
  LMode3:         " �r nu i ~kort~ utskriftsl�ge, vilket alltid ger korta
                   beskrivningar av platser
                   (�ven om du inte har varit d�r f�rut).";
  Lock:    switch(n)
           {   1: print_ret (CDenEllerHan) x1, " verkar inte vara n�got du kan l�sa.";
               2: print_ret (CDenEllerHan) x1, " �r redan ",(indefadjlocked) x1,".";
               3: "F�rst m�ste du st�nga ", (the) x1, ".";
               4: print_ret (CDenEllerHan) x1, " verkar inte passa l�set.";
               5:  "Du l�ser ", (the) x1, ".";
           }
  Look:    switch(n)
           {   1: print " (p� ", (the) x1, ")";
               2: print " (i ", (the) x1, ")";
               3: print " (som ", (object) x1, ")";
               4: print "^P� ", (the) x1;
                  WriteListFrom(child(x1),
                    ENGLISH_BIT+RECURSE_BIT+PARTINV_BIT+TERSE_BIT+CONCEAL_BIT+ISARE_BIT);
                  ".";
               5,6:
                   if (x1 ~= location) {
                       if (x1 has supporter) print "^P� "; else print "^I ";
                       print (the) x1, " kan du";
                   }
                   else print "^Du kan";
                   if (n==5) print " ocks�";
                   print " se ";
                   WriteListFrom(child(x1),
                     ENGLISH_BIT+RECURSE_BIT+PARTINV_BIT+TERSE_BIT+CONCEAL_BIT+WORKFLAG_BIT);
                   if (x1 ~= location) ".";
                   " h�r.";
               7:  "Du ser inget s�rskilt i den riktningen.";
           }
  LookUnder: switch(n)
           {   1: "Men det �r ju m�rkt.";
               2: "Du hittar inget av intresse.";
           }
  Mild:           "Precis vad jag t�nkte.";
  Miscellany:
           switch(n)
           {   1: "(tar bara h�nsyn till de f�rsta sexton f�rem�len)^";
               2: "Inget att g�ra!";
               3: print " Du har d�tt ";
               4: print " Du har vunnit ";
               5: print "^Vill du B�RJA OM, H�MTA ett sparat spel";
                  #IFDEF DEATH_MENTION_UNDO;
                  print ", �NGRA ditt senaste drag";
                  #ENDIF;
                  if (TASKS_PROVIDED==0)
                      print ", visa FULL information om dina po�ng";
                  if (deadflag==2 && AMUSING_PROVIDED==0)
                      print ", se n�gra f�rslag p� ROLIGA saker att prova";
                  " eller SLUTA?";
               6: "[Din speltolk har tyv�rr inte ~�ngra~.]";
               7: "~�ngra~ misslyckades.  [Det �r inte alla speltolkar som har ~�ngra~.]";
               8: "Skriv ett av svaren ovan.";
               9: "^Nu �r det kolsvart h�r inne!";
              10: "Urs�kta?";
              11: "[Du kan inte ~�ngra~ n�got som du inte har gjort!]";
              12: "[Du kan tyv�rr inte ~�ngra~ tv� g�nger i rad.]";
              13: "[Senaste draget �ngrat.]";
              14: "Tyv�rr, det kan inte r�ttas till.";
              15: "Det var s� lite s�.";
              16: "~Hoppsan~ kan bara r�tta till ett enda ord.";
              17: "Det �r kolsvart, och du kan inte se n�gonting alls.";
              18: print "dig sj�lv";
              19: "Lika snygg som alltid.";           
              20: "F�r att upprepa ett kommando som ~groda, hoppa~, skriv bara
                   ~igen~, inte ~groda, igen~.";
              21: "Det verkar inte rimligt att g�ra det igen.";
              22: "Du kan inte b�rja en mening med ett komma.";
              23: "Du verkar vilja prata med n�gon, men jag f�rst�r inte vem.";
              24: "Du kan inte prata med ", (the) x1, ".";
              25: "F�r att prata med n�gon, prova ~n�gon, hej~ eller n�got liknande.";
              26: "(tar f�rst upp ", (the) not_holding, ")";
              27: "Den meningen f�rstod jag inte.";
              28: print "Jag tror jag f�rstod ~";
              29: "Det talet f�rstod jag inte.";
              30: "N�gon s�dan ser du inte till.";
              31: "Du verkar ha sagt f�r lite!";
              32: print_ret (CDenEllerHonom) x1, " h�ller du inte i!"; ! �#� Could be rephrased to include the correct Den/Det, using ThatorThose?
              33: "Du kan inte anv�nda flera f�rem�l med det verbet.";
              34: "Du kan bara anv�nda flera f�rem�l en g�ng per rad.";
              35: "Jag �r inte s�ker p� vad ~", (address) pronoun_word,
                  "~ refererar till.";
              36: "Du undantog n�got som �nd� inte var med!";
              37: "Det kan du bara g�ra med n�got levande.";
              38: "Det verbet k�nner jag inte igen.";
              39: "Det �r inte n�got du har n�gon anv�ndning av i det h�r spelet.";
              40: "Du kan inte se ~", (address) pronoun_word,
                  "~ (", (the) pronoun_obj, ") just nu.";
              41: "Jag f�rstod inte riktigt den avslutningen.";
              42: print "Det finns ";
                  if (x1==0) print "inga";
                  else { print "bara "; LanguageNumber(x1, 0, multiple_object-->1); }
                  if (x1==1) {
                    if(multiple_object-->1 has neuter)
                      " s�dant tillg�ngligt.";
                    " s�dan tillg�nglig.";
                  } else
                    " s�dana tillg�ngliga."; ! �#� Tries to care about gender
              43: "Inget att g�ra!";
              44: switch(action_to_be) {
                    ##Drop, ##Insert, ##PutOn: "Du har inget att sl�ppa!";
                    default: "Det finns inget att ta!";
                  }
              45: print "Vem menar du, ";
              46: print "Menar du ";
              47: "Tyv�rr kan du bara ange ett f�rem�l h�r. Exakt vilket menar du?";
              48: print "Jag antar att du menar ~"; ! �#� This message should work now
                  if (actor~=player) print (name) actor, ", ";
                  PrintCommand();
                  style bold;
                  print " n�gon";
                  style roman;
                  print "~, men vem?^";
              49: print "Jag antar att du menar ~";
                  if (actor~=player) print (the) actor, ", ";
                  PrintCommand();
                  style bold;
                  print " n�got";
                  style roman;
                  print "~, men vad?^";
!              50: print "Din po�ng har just g�tt ";
!                  if (x1 > 0) print "upp"; else { x1 = -x1; print "ner"; }
!                  print " med ", (number) x1, " po�ng";
              50: print "Du ";
                  if (x1 > 0) print "fick"; else { x1 = -x1; print "f�rlorade"; }
                  print " just "; 
                  LanguageNumber(x1,false,false,neuter); 
                  print " po�ng";
              51: "(Eftersom n�got dramatiskt har h�nt
                   har din sekvens av kommandon avbrutits.)";
              52: "^Skriv ett tal mellan 1 och ", x1,
                  ", 0 f�r att visa det h�r igen eller tryck RETURN.";
              53: "^[Tryck MELLANSLAG.]";
              54: "[Kommentar sparad.]";
              55: "[Kommentar INTE sparad.]";
              56: "~, men sedan tappade du bort mig.";
              57: print "?^";
           }
  NotifyOn:       "Po�ngmeddelanden p�slaget.";
  NotifyOff:      "Po�ngmeddelanden avslaget.";
  Objects: switch(n)
           {   1: "F�rem�l du har anv�nt:^";
               2: "Inga.";
               3: print "   (",(indefadjworn) x1,")"; ! �#� Is x1 actually set to the object# in question here? (It is now)
               4: print "   (",(indefadjheld) x1,")"; ! �#� Is x1 actually set to the object# in question here? (It is now)
               5: print "   (",(indefadjgiven) x1,")"; ! �#� Is x1 actually set to the object# in question here? (It is now)
               6: print "   (i ", (name) x1, ")";
               7: print "   (i ", (the) x1, ")";
               8: print "   (inuti ", (the) x1, ")";
               9: print "   (p� ", (the) x1, ")";
              10: print "   (borta)";
           }
  Open:    switch(n)
           {   1: print_ret (CDenEllerHan) x1,
                  " kan inte �ppnas.";
               2: print_ret (CDenEllerHan) x1," verkar ",(indefadjlocked) x1,".";
               3: print_ret (CDenEllerHan) x1," �r redan ",(indefadjopen) x1,".";
               4: print "Du �ppnar ", (the) x1, " och finner d� ";
                  if (WriteListFrom(child(x1),
                      ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT)==0) "nothing.";
                  ".";
               5: "Du �ppnar ", (the) x1, ".";
           }
  Order:          print_ret (The) x1," har viktigare saker f�r sig.";
  Places: switch (n) {
        1:  print "Du har bes�kt: ";
        2:  print ".^";
    }
  Pray:           "Inget direkt uppenbart h�nder.";
  Pronouns: switch(n)
           {   1: print "F�r tillf�llet refererar ";
               2: print "till ";
               3: print "inte till n�got s�rskilt";
               4: "inga pronomen till n�got alls.";
               5: ".";
           }
  Pull, Push, Turn:
           switch(n)
           {   1: print_ret (CDenEllerHan) x1, " sitter fast.";
               2: "Det misslyckas.";
               3: "Inget verkar h�nda.";
               4: "Det vore direkt ohyfsat.";
           }
  PushDir: switch(n)
           {   1: "Var det det b�sta du kunde komma p�?";
               2: "Det �r ingen riktning.";
               3: "I den riktningen g�r det i alla fall inte.";
           }
  PutOn:   switch(n)
           {   1: "Du m�ste h�lla i ", (the) x1,
                  " innan du kan l�gga ", (DenEllerHonom) x1,
                  " p� n�got annat.";
               2: "Du kan inte l�gga n�got p� sig sj�lvt.";
               3: "Att l�gga saker p� ", (the) x1, " skulle inte leda n�gon vart.";
               4: "Du �r inte smidig nog.";
               5: "(tar f�rst av ", (DenEllerHonom) x1, ")^";
               6: "Det finns inte plats f�r n�got mer p� ", (the) x1, ".";
               7: "Gjort.";
               8: "Du placerar ", (the) x1, " p� ", (the) second, ".";
           }
  Quit:    switch(n)
           {   1: print "Svara ja eller nej.";
               2: print "�r du s�ker p� att du vill sluta? ";
           }
  Remove:  switch(n)
           {   1: print_ret (CDenEllerHan) x1, " �r tyv�rr in",(indefadjclosed) x1, ".";
               2: print_ret "Men ",(DenEllerHan) x1, " �r inte d�r nu.";
               3: "Borttagen.";
           }
  Restart: switch(n)
           {   1: print "�r du s�ker p� att du vill b�rja om? ";
               2: "Misslyckades.";
           }
  Restore: switch(n)
           {   1: "H�mtningen misslyckades.";
               2: "Ok.";
           }
  Rub:            "Det ger inget anv�ndbart resultat.";
  Save:    switch(n)
           {   1: "Sparningen misslyckades.";
               2: "Ok.";
           }
  Score:   switch (n) {
               1: if (deadflag) print "I det spelet fick du ";
                  else print "Du har hittills f�tt ihop ";
                  print score, " po�ng av ", MAX_SCORE,
                  " m�jliga p� ", turns, " drag";
                  return;
               2: "Det finns inga po�ng i detta spel.";
           }
  ScriptOn: switch(n)
           {   1: "Utskrift �r redan p�slaget.";
               2: "H�r b�rjar en utskrift av";
               3: "F�rs�ket att p�b�rja en utskrift misslyckades.";
           }
  ScriptOff: switch(n)
           {   1: "Utskrift �r redan avslaget.";
               2: "^H�r slutar utskriften.";
               3: "F�rs�ket att avsluta utskriften misslyckades.";
           }
  Search:  switch(n)
           {   1: "Men det �r ju m�rkt.";
               2: "Det finns inget p� ", (the) x1, ".";
               3: print "P� ", (the) x1;
                  WriteListFrom(child(x1),
                      TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
                  ".";
               4: "Du hittar inget av intresse.";
               5: "Du ser inte vad som finns i ", (the) x1, ", eftersom ",
                  (DenEllerHan) x1, " �r ",(indefadjclosed) x1,".";
               6: print_ret (The) x1, " �r ",(indefadjempty) x1,".";
               7: print "I ", (the) x1;
                  WriteListFrom(child(x1),
                      TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
                  ".";
           }
  Set:            "Nej, du kan inte s�tta ", (DenEllerHonom) x1, ".";
  SetTo:          "Nej, du kan inte s�tta ", (DenEllerHonom) x1, " till n�got.";
  Show:    switch(n)
           {   1: "Du h�ller inte i ", (the) x1, ".";
               2: print (The) x1, " �r inte imponera";
                  if (x1 has pluralname) "de.";
                  if (x1 has neuter) "t."; else "d.";
           }
  Sing:           "Din s�ngr�st �r inte mycket att hurra f�r.";
  Sleep:          "Du k�nner dig inte direkt s�mnig.";
  Smell:          "Du k�nner inga ov�ntade lukter.";
  Sorry:          "Det �r okej. F�r den h�r g�ngen.";
  Squeeze: switch(n)
           {   1: "Tafsa inte!";
               2: "Det ger inget m�rkbart resultat.";
           }
  Strong:         "Riktiga �ventyrare anv�nder inte s�dana ord.";
  Swim:           "Det finns inte s� mycket vatten att simma i.";
  Swing:          "Det finns just inget vettigt att gunga h�r.";
  SwitchOn: switch(n)
           {   1: print_ret (CDenEllerHan) x1," verkar inte vara n�got du kan sl� av och p�.";
               2: print_ret (DenEllerHan) x1,
                  " �r redan p�.";
               3: "Du sl�r p� ", (the) x1, ".";
           }
  SwitchOff: switch(n)
           {   1: print_ret (CDenEllerHan) x1," verkar inte vara n�got du kan sl� av och p�.";
               2: print_ret (CDenEllerHan) x1,
                  " �r redan av.";
               3: "Du sl�r av ", (the) x1, ".";
           }
  Take:    switch(n)
           {   1: print "Tag";
                  if(noun has pluralname) "na.";
                  if(noun has neuter) "et."; else "en.";
               2: "Du �r alltid sj�lvupptagen.";
               3: "Det vill ",(DenEllerHan) x1," nog inte.";
               4: print_ret "D� m�ste du f�rst l�mna ",(the) x1, ".";
               5: "Du har redan ", (DenEllerHonom) x1, ".";
               6: print_ret (CDenEllerHan) noun, " verkar tillh�ra ", (the) x1, ".";
               7: print_ret (CDenEllerHan) noun, " verkar vara en del av ", (the) x1, ".";
               8: print_ret "Du kan inte komma �t ",(DenEllerHonom) x1, "."; ! �#� This must be modified to handle neuter correctly
               9: print_ret (The) x1, " �r inte ",(indefadjopen) x1, ".";
              10: print_ret "Du kan knappast flytta ", (DenEllerHonom) x1, ".";
              11: print_ret (CDenEllerHan) x1, " sitter fast.";
              12: "Du b�r redan p� f�r mycket.";
              13: "(l�gger ", (the) x1, " i ", (the) SACK_OBJECT,
                  " f�r att f� plats)";
           }
  Taste:          "Du k�nner ingen ov�ntad smak.";
  Tell:    switch(n)
           {   1: "Du pratar lite med dig sj�lv.";
               2: "Ingen reaktion.";
           }
  Think:          "En utm�rkt id�!";
  ThrowAt: switch(n)
           {   1: "Meningsl�st.";
               2: "N�r det v�l kommer till kritan v�gar du inte.";
           }
  Touch:   switch(n)
           {   1: "Bort med tassarna!";
               2: "Det k�nns ungef�r som du hade f�rv�ntat dig.";
               3: "Om du tror att det hj�lper, s� visst.";
           }
  TranscribeOn:
           switch(n)
           {   1: "Transkriptionsl�ge �r redan p�slaget.";
               2: "Transkriptionsl�ge p�slaget. ~aa~ betyder nu �, ~ae~ betyder �
                   och ~oe~ betyder �. Skriv ett utropstecken f�re varje s�dan 
                   bokstavskombination som INTE ska transkriberas, som t ex i ~oeppna b!oetten~.
                   Skriv ~transkription visa~ f�r att f� meddelande n�r transkription anv�nds.";
           }
  TranscribeOff:   
           switch(n)
           {   1: "Transkriptionsl�ge �r redan avslaget.";
               2: "Transkriptionsl�ge avslaget.";
           }
  TranscribeShow:
           switch(n)
           {   1: "Transkriptionsl�ge med visning �r redan p�slaget.";
               2: "Transkriptionsl�ge med visning p�slaget. ~aa~ betyder nu �, ~ae~ betyder �
                   och ~oe~ betyder �. Skriv ett utropstecken f�re varje s�dan 
                   bokstavskombination som INTE ska transkriberas, som t ex i ~oeppna b!oetten~.";
           }
  Unlock:  switch(n)
           {   1: print_ret (CDenEllerHan) x1, " verkar inte vara n�got du kan l�sa upp.";
               2: print_ret (CDenEllerHan) x1," �r redan o",(indefadjlocked) x1,".";
               3: print_ret (CDenEllerHan) x1, " verkar inte passa l�set.";
               4: "Du l�ser upp ", (the) x1, ".";
           }
  VagueGo:       "Du m�ste tala om i vilken kompassriktning du vill g�.";
  Verify:  switch(n)
           {   1: "Spelfilen testades och verkar vara intakt.";
               2: "Spelfilen testades men verkar inte vara intakt.
                   Det kan finnas allvarliga fel p� den.";
           }
  Wait:           "Du v�ntar.";
  Wake:           "Den grymma sanningen �r att det h�r inte �r n�gon dr�m.";
  WakeOther:      "Det verkar on�digt.";
  Wave:    switch(n)
           {   1: "Men du h�ller inte i ", (DenEllerHonom) x1, ".";
               2: "Du ser f�nig ut n�r du viftar med ", (the) x1, ".";
           }
  WaveHands:      "Du vinkar, �ven om det k�nns lite f�nigt.";
  Wear:    switch(n)
           {   1: "Du kan inte ta p� dig ", (DenEllerHonom) x1, "!";
               2: "Du h�ller inte i ", (DenEllerHonom) x1, "!";
               3: print_ret (CDenEllerHonom) x1, " har du redan p� dig!";
               4: "Du tar p� dig ", (the) x1, ".";
           }
  Yes, No:        "Det var en retorisk fr�ga.";
];

! ==============================================================================

Constant LIBRARY_SWEDISH;       ! for dependency checking.

! ==============================================================================
