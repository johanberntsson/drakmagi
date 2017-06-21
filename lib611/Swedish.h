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

! Konventioner i källkoden:
! *#* betyder kvarvarande problem
! ¤#¤ betyder åtgärdat problem

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

Constant LanguageVersion = "Översättning av biblioteket till svenska (c) Fredrik Ramsberg 2003-2004";

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
    ! ¤#¤ Must first check if first character is actually shiftable, and check for accented characters
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
  print  "Kollar efter följande (möjliga) problem:^* Saknar både short_name_def och short_name.
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
      print "Saknar både short_name_def och short_name";
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
                    with door_dir n_to, name 'n//' 'norra' 'norr' 'norrut' 'norröver' 'nord';
CompassDirection -> s_obj "söder"
                    with door_dir s_to, name 's//' 'södra' 'söder' 'söderut' 'söderöver' 'syd';
CompassDirection -> e_obj "öster"
                    with door_dir e_to, name 'ö//' 'östra' 'öster' 'österut' 'öst' 'östöver' 'österöver' 'o//';
CompassDirection -> w_obj "väster"
                    with door_dir w_to, name 'v//' 'västra' 'väster' 'västerut' 'väst' 'västöver' 'västeröver';
CompassDirection -> ne_obj "nordost"
                    with door_dir ne_to, name 'nö' 'no' 'nordöstra' 'nordöster' 'nordöst' 'nordost';
CompassDirection -> nw_obj "nordväst"
                    with door_dir nw_to, name 'nv' 'nordvästra' 'nordväster' 'nordväst';
CompassDirection -> se_obj "sydost"
                    with door_dir se_to, name 'sö' 'so' 'sydöstra' 'sydöster' 'sydöst' 'sydost';
CompassDirection -> sw_obj "sydväst"
                    with door_dir sw_to, name 'sv' 'sydvästra' 'sydväster' 'sydväst';
CompassDirection -> u_obj "upp"
                    with door_dir u_to, name 'u//' 'upp' 'uppåt' 'tak' 'taket' 'himlen' 'skyn';
CompassDirection -> d_obj "marken"
                    with door_dir d_to, name 'ner' 'neråt' 'golv' 'golvet' 'mark' 'marken' 'ned' 'nedåt';
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
Constant OOPS2__WD    = 'ojdå';
Constant OOPS3__WD    = 'ojsan';
Constant UNDO1__WD    = 'ogör';
Constant UNDO2__WD    = 'ångra';
Constant UNDO3__WD    = 'ångra';

Constant ALL1__WD     = 'alla';
Constant ALL2__WD     = 'varje';
Constant ALL3__WD     = 'allihop';
Constant ALL4__WD     = 'samtliga';
Constant ALL5__WD     = 'allt';
Constant AND1__WD     = 'och';
Constant AND2__WD     = 'samt';
Constant AND3__WD     = 'även';
Constant BUT1__WD     = 'utom';
Constant BUT2__WD     = 'förutom';
Constant BUT3__WD     = 'utom';
Constant ME1__WD      = 'jag';
Constant ME2__WD      = 'mig';
Constant ME3__WD      = 'själv';
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
Constant NO3__WD      = 'nä';
Constant YES1__WD     = 'j//';
Constant YES2__WD     = 'ja';
Constant YES3__WD     = 'jo';

Constant AMUSING__WD  = 'roliga';
Constant FULLSCORE1__WD = 'fullpoäng';
Constant FULLSCORE2__WD = 'full';
Constant QUIT1__WD    = 'avsluta';
Constant QUIT2__WD    = 'sluta';
Constant RESTART__WD  = 'börja';
Constant RESTORE__WD  = 'hämta';

! ¤#¤ The need for uter, in addition to male, female and neuter,
! necessitates the adding of four bits to every GNA-word. While
! there was indeed room for these bits, it still implies that
! one or more of the other library files will have to be modified
! as well to interpret these words correctly in order to handle
! the four genders correctly.

Array LanguagePronouns table ! ¤#¤ Usage of this array must be modified to add uter

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
!      'dom'    $$0000111100001111                NULL; !¤#¤ Decided to leave this out because it gets ugly when player types "pronomen" (pronouns)

Array LanguageDescriptors table ! ¤#¤ Usage of this array must be modified to add uter

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
      'den'    $$1110000011100000 DEFART_PK       NULL ! ¤#¤ These have been commented out because their usage
      'det'    $$0001000000010000 DEFART_PK       NULL !     as definite articles conflict with their usage as
      'de'     $$0000111100001111 DEFART_PK       NULL !     it-words. Should be corrected in the parser somehow.
      'en'     $$1110000011100000 INDEFART_PK     NULL
      'ett'    $$0001000000010000 INDEFART_PK     NULL
      'några'  $$0000111100001111 INDEFART_PK     NULL
      'tänd'   $$1110000011100000 light           NULL
      'tänt'   $$0001000000010000 light           NULL
      'tända'  $$1111111111111111 light           NULL
      'tände'  $$1000000010000000 light           NULL
      'släckt' $$1111000011110000 (-light)        NULL
     'släckte' $$1000000010000000 (-light)        NULL
     'släckta' $$1111111111111111 (-light)        NULL;

Array LanguageNumbers table
    'en' 1 'ett' 1 'två' 2 'tvenne' 2 'tre' 3 'trenne' 3 'fyra' 4 'fem' 5
    'sex' 6 'sju' 7 'åtta' 8 'nio' 9 'tio' 10
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

! This section handles transciption of aa, ae and oe into å, ä and ö respectively

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
          cnew='å';
        if(c2=='e')
          cnew='ä';
      }
      if(c1=='o' && c2=='e')
        cnew='ö';
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

! This section changes "mig själv" to "mig", to avoid a pronoun consisting of two words

#ifdef TARGET_ZCODE;
  for(i=2:i<=parse->1:i++)
    if(parse-->(2*i-1)=='själv' && parse-->(2*i-3)=='mig' or 'mej') {
      LTI_delete((parse->(4*i+1))-1,(parse->(4*i))+1);
      Tokenise__(buffer,parse);
    }
#ifnot; ! TARGET_GLULX
  for(i=2:i<=parse-->0:i++)
    if(parse-->(3*i-2)=='själv' && parse-->(3*i-5)=='mig' or 'mej') {
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
  x=text; ! ¤#¤ Only here to avoid a warning
  return 0;
];

Array LanguageArticles -->

 !   Contraction form 0:
 !   Cdef   Def    Indef

! ¤#¤ Cdef and Def should not be printed unless there is an adjective before the noun

     "Den " "den " "en "        ! masc/fem/uter sing
     "Det " "det " "ett "       ! neuter sing
     "De "  "de "  "några ";    ! plural

                   !             a               i
                   !             s       p       s       p
                   !             m f u n m f u n m f u n m f u n

Array LanguageGNAsToArticles --> 0 0 0 1 2 2 2 2 0 0 0 1 2 2 2 2; ! ¤#¤ Usage of this array must be modified to add uter

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
       s_to: print "söderut";
       e_to: print "österut";
       w_to: print "västerut";
       ne_to: print "nordost";
       nw_to: print "nordväst";
       se_to: print "sydost";
       sw_to: print "sydväst";
       u_to: print "uppåt";
       d_to: print "neråt";
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
  {   1:  if(force_neuter_1) { print "ett"; return ENDS_WITH_T; } else print "en"; ! ¤#¤ This could also be "ett", if printing how many objects of a certain kind there are, and the objects are neuter
      2:  print "två";
      3:  print "tre";
      4:  print "fyra";
      5:  print "fem";
      6:  print "sex";
      7:  print "sju";
      8:  print "åtta";
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
             8: print "åttio";
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
      'lista': print "lista dina tillhörigheter";
      't//':   print "titta";
      'x//':   print "undersök";
      'z//':   print "vänta";
      'inspelning':     print "inspelning";
      'meddelanden':    print "meddelanden";
      'substantiv':     print "substantiv";
      'transkribera':   print "transkribera";
      'transkription':  print "transkription";
      'uppspelning':    print "uppspelning";
      'dubbeltusan':    print "dubbeltusan";
      'järnspikar':     print "järnspikar";
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
    if (w == 'titta' or 'gå' or 'spring' or 'flytta' or 'tryck' or 'knuffa' 
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
    if (w == 'full' or 'lång' or 'långt' or 'långa' or 'normalt' or 'normal'
          or 'normala' or 'kort' or 'korta' or 'visa' or 'öppna' or 'vakna'
          or 'tänd')
        rtrue;
    rfalse;
];


Constant NKEY__TX     = "N=nästa ämne";
Constant PKEY__TX     = "F=föregående";
Constant QKEY1__TX    = "X=åter till spelet";
Constant QKEY2__TX    = "X=föregående meny";
Constant RKEY__TX     = "RETURN=läs ämne";

Constant NKEY1__KY    = 'N';
Constant NKEY2__KY    = 'n';
Constant PKEY1__KY    = 'F';
Constant PKEY2__KY    = 'f';
Constant QKEY1__KY    = 'X';
Constant QKEY2__KY    = 'x';

Constant SCORE__TX    = "Poäng: ";
Constant MOVES__TX    = "Drag: ";
Constant TIME__TX     = "Tid: ";
Constant CANTGO__TX   = "Du kan inte gå däråt.";
Constant FORMER__TX   = "ditt tidigare jag";
Constant YOURSELF__TX = "dig själv";
Constant YOU__TX      = "Du";
Constant DARKNESS__TX = "Mörker";

Constant THOSET__TX   = "dem";
Constant THAT__TX     = "den"; ! ¤#¤ Should this be "det" in case we're talking about something neuter?
Constant OR__TX       = " eller ";
Constant NOTHING__TX  = "ingenting";
Constant IS__TX       = " är";
Constant ARE__TX      = " är";
Constant IS2__TX      = "är ";
Constant ARE2__TX     = "är ";
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
  if (obj has neuter) { print "det"; return; } ! ¤#¤ This must be modified to cover uter as well!
  if (obj has female) { print "hon"; return; }
  print "han";
];
[ CDenEllerHan obj;   ! Used in the accusative
  SetGender(obj);
  if (obj == player) { print "Du"; return; }
  if (obj has pluralname) { print "De"; return; }
  if (obj has uter) { print "Den"; return; }
  if (obj has neuter) { print "Det"; return; } ! ¤#¤ This must be modified to cover uter as well!
  if (obj has female) { print "Hon"; return; }
  print "Han";
];
[ DenEllerHonom obj;   ! Used in the accusative
  SetGender(obj);
  if (obj == player) { print "dig själv"; return; }
  if (obj has pluralname) { print "dem"; return; }
  if (obj has uter) { print "den"; return; }
  if (obj has neuter) { print "det"; return; } ! ¤#¤ This must be modified to cover uter as well!
  if (obj has female) { print "henne"; return; }
  print "honom";
];
[ CDenEllerHonom obj;   ! Used in the accusative
  SetGender(obj);
  if (obj == player) { print "Dig själv"; return; }
  if (obj has pluralname) { print "Dem"; return; }
  if (obj has uter) { print "Den"; return; }
  if (obj has neuter) { print "Det"; return; } ! ¤#¤ This must be modified to cover uter as well!
  if (obj has female) { print "Henne"; return; }
  print "Honom";
];

[ IndefAdjOpen obj;
  if (obj hasnt pluralname) {
    if (obj has neuter) { print "öppet"; return; }
    print "öppen"; return;
  }
  print "öppna";
];
[ IndefAdjClosed obj;
  if (obj hasnt pluralname) {
    if (obj has neuter) { print "stängt"; return; }
    print "stängd"; return;
  }
  print "stängda";
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
    if (obj has neuter) { print "påtaget"; return; }
    print "påtagen"; return;
  }
  print "påtagna";
];
[ IndefAdjLocked obj;
  if (obj hasnt pluralname) { print "låst"; return; }
  print "låsta";
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

  Answer, Ask:    "Du får inget svar.";
  Attack:         "Våld är knappast lösningen här.";
  Blow:           "Det vore meningslöst att blåsa på ", (DenEllerHonom) x1, ".";
  Burn:           "Det vore farligt och föga produktivt.";
  Buy:            "Det finns just inget att köpa.";
  Climb:          "Det verkar inte så konstruktivt.";
  Close:   switch(n)
           {   1: print_ret (CDenEllerHan) x1,"  är inte något du kan stänga.";
               2: print_ret (CDenEllerHan) x1,
                  " är redan ",(indefadjclosed) x1,".";
               3: "Du stänger ", (the) x1, ".";
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
        3: "[Kommandoinspelning var redan påslagen.]";
        4: "[Kommandoinspelning misslyckades.]";
        #Endif; ! TARGET_
    }
  CommandsRead: switch (n) {
        1: "[Spelar upp kommandon.]";
        #Ifdef TARGET_GLULX;
        2: "[Kommandon håller redan på att spelas upp.]";
        3: "[Uppspelning av kommandon misslyckades. Kommandoinspelning pågår.]";
        4: "[Uppspelning av kommandon misslyckades.]";
        5: "[Uppspelning av kommandon avlsutad.]";
        #Endif; ! TARGET_
    }
  Consult:        "Du upptäcker inget intressant i ", (the) x1, ".";
  Cut:            "Att skära i ", (DenEllerHonom) x1, " verkar inte särskilt konstruktivt.";
  Dig:            "Det kan inte ge så mycket att gräva här.";
  Disrobe: switch(n)
           {   1: print_ret (CDenEllerHonom) x1, " har du inte på dig.";
               2: "Du tar av ", (the) x1, ".";
           }
  Drink:          "Det finns inget värt att dricka här.";
  Drop:    switch(n)
           {   1: print_ret (CDenEllerHan) x1, " är redan här.";
               2: "Du har inte ", (DenEllerHonom) x1, ".";
               3: "(tar först av ", (the) x1, ")";
               4: "Släppt.";
           }
  Eat:     switch(n)
           {   1: print (CDenEllerHan) x1," är helt enkelt oätlig";
                  if(x1 has pluralname) "a.";
                  if(x1 has neuter) "t."; else ".";
               2: "Du äter ", (the) x1, ". Inte illa.";
           }
  EmptyT:  switch(n)
           {   1: print_ret (The) x1, " kan inte innehålla saker.";
               2: print_ret (The) x1, " är ",(indefadjclosed) x1,".";
               3: print_ret (The) x1, " är redan ",(indefadjempty) x1,".";
               4: "Det skulle just inte tömma någonting alls.";
           }
  Enter:   switch(n)
           {   1: print "Men du är ju redan ";
                  if (x1 has supporter) print "på "; else print "i ";
                  print_ret (the) x1, ".";
               2: print (CDenEllerHan) x1, " är inte till för "; ! ¤#¤ Should be more varied.
                  switch (verb_word) {
                      'stå','ställ': "att stå på.";
                      'sitt': "att sitta på.";
                      'ligg': "att ligga på.";
                      default: "det.";
                  }
               3: print_ret (The) x1, " är ",(indefadjclosed) x1,", så det blir nog svårt.";
               4: "Först måste du stå på dina egna fötter igen.";
               5: switch (verb_word) {
                      'stå','ställ': print "Du ställer dig";
                      'sitt','sätt': print "Du sätter dig";
                      'ligg','lägg': print "Du lägger dig";
                      default: print "Du kliver "; if(x1 has supporter) print "upp"; else print "in";
                  }
                  if (x1 has supporter) print " på "; else print " i ";
                  print_ret (the) x1, ".";
               6: "(du lämnar ",(the) x1, ")";
               7: if (x1 has supporter) "(kliver på ", (the) x1, ")^";
                  if (x1 has container) "(kliver in i ", (the) x1, ")^";
                  "(går på ", (the) x1, ")^";
           }
  Examine: switch(n)
           {   1: "Mörker, substantiv. En frånvaro av ljus att se i.";
               2: "Du ser inget speciellt med ", (the) x1, ".";
               3: print (The) x1, " är just nu ";
                  if (x1 has on) "på."; else "av.";
           }
  Exit:    switch(n)
           {   1: "Men du är ju inte i något för tillfället.";
               2: "Det kan bli svårt, efterom ", (the) x1, " är ",(indefadjclosed) x1,".";
               3: "Du lämnar ",(the) x1, ".";
               4: print "Men du är inte ";
                  if (x1 has supporter) print "på "; else print "i ";
                  print_ret (the) x1, ".";
           }
  Fill:           "Men det finns inget vatten här att fylla på.";
  FullScore: switch(n)
           {   1: if (deadflag) print "Du fick ";
                  else          print "Du har ";
                  "poäng, fördelat enligt följande:^";
               2: "hitta viktiga föremål";
               3: "besöka viktiga platser";
               4: print "totalt (av ", MAX_SCORE; ")";
           }
  GetOff:         "Men du är ju inte på ", (the) x1, " för tillfället.";
  Give:    switch(n)
           {   1: "Du håller inte i ", (the) x1, ".";
               2: "Du bollar lite med ", (the) x1,
                  ", men det ger inte så mycket.";
               3: print_ret (The) x1, " verkar inte bry sig om ditt erbjudande.";
           }
  Go:      switch(n)
           {   1: print "Först måste du kliva ";
                  if (x1 has supporter) print "av "; else print "ur ";
                  print_ret (the) x1, ".";
               2: print_ret (string) CANTGO__TX;   ! "You can't go that way."
               3: "Du kan inte klättra upp på ", (the) x1, ".";
               4: "Du kan inte klättra ner på ", (the) x1, ".";
               5: "Det blir svårt, eftersom ", (the) x1, " är i vägen.";
               6: "Det kan du inte, eftersom ", (the) x1," inte leder någonstans.";
           }
  Insert:  switch(n)
           {   1: "Du måste hålla i ", (the) x1,
                  " innan du kan lägga ", (DenEllerHonom) x1,
                  " i något annat.";
               2: print_ret (CDenEllerHan) x1, " kan inte innehålla saker.";
               3: print_ret (The) x1, " är ",(indefadjclosed) x1,".";
               4: "Först måste du ta av ", (DenEllerHonom) x1, ".";
               5: "Du kan inte lägga något i sig självt.";
               6: "(tar först av ", (DenEllerHonom) x1, ")^";
               7: "Det finns inte plats för något mer i ", (the) x1, ".";
               8: "Gjort.";
               9: "Du placerar ", (the) x1, " i ", (the) second, ".";
           }
  Inv:     switch(n)
           {   1: "Du har ingenting.";
               2: print "Du har";
               3: print ":^";
               4: print ".^";
           }
  Jump:           "Du hoppar på stället. Det ger inget.";
  JumpOver, Tie:  "Det skulle inte vara till någon större hjälp.";
  Kiss:           "Tänk lite mer på spelet istället.";
  Listen:         "Du hör inget oväntat.";
  ListMiscellany:
           switch(n)
           {   1: print " (lyser)";
               2: print " (",(indefadjclosed) x1,")";
               3: print " (som är ",(indefadjclosed) x1," och lyser)";
               4: print " (",(indefadjempty) x1,")";
               5: print " (som är ",(indefadjempty) x1," och lyser)";
               6: print " (som är ",(indefadjclosed) x1," och ",(indefadjempty) x1,")";
               7: print " (som är ",(indefadjclosed) x1,", ",(indefadjempty) x1," och lyser)";
               8: print " (som lyser och är ",(indefadjworn) x1;
               9: print " (lyser";
              10: print " (",(indefadjworn) x1;
              11: print " (som ";
              12: print "är ", (indefadjopen) x1;
              13: print "är ", (indefadjopen) x1," men ",(indefadjempty) x1;
              14: print "är ", (indefadjclosed) x1;
              15: print "är ", (indefadjclosed) x1," och ",(indefadjlocked) x1;
              16: print " och ",(indefadjempty) x1;
              17: print " (som är ",(indefadjempty) x1,")";
              18: print " innehållande ";
              19: print " (på ";
              20: print ", ovanpå ";
              21: print " (i ";
              22: print ", inuti ";
           }
  LMode1:         " är nu i ~normalt~ utskriftsläge, vilket ger
                    långa beskrivningar av platser du aldrig varit på tidigare
                    och annars korta beskrivningar.";
  LMode2:         " är nu i ~långt~ utskriftsläge, vilket alltid ger långa
                   beskrivningar av platser
                   (även om du har varit där förut).";
  LMode3:         " är nu i ~kort~ utskriftsläge, vilket alltid ger korta
                   beskrivningar av platser
                   (även om du inte har varit där förut).";
  Lock:    switch(n)
           {   1: print_ret (CDenEllerHan) x1, " verkar inte vara något du kan låsa.";
               2: print_ret (CDenEllerHan) x1, " är redan ",(indefadjlocked) x1,".";
               3: "Först måste du stänga ", (the) x1, ".";
               4: print_ret (CDenEllerHan) x1, " verkar inte passa låset.";
               5:  "Du låser ", (the) x1, ".";
           }
  Look:    switch(n)
           {   1: print " (på ", (the) x1, ")";
               2: print " (i ", (the) x1, ")";
               3: print " (som ", (object) x1, ")";
               4: print "^På ", (the) x1;
                  WriteListFrom(child(x1),
                    ENGLISH_BIT+RECURSE_BIT+PARTINV_BIT+TERSE_BIT+CONCEAL_BIT+ISARE_BIT);
                  ".";
               5,6:
                   if (x1 ~= location) {
                       if (x1 has supporter) print "^På "; else print "^I ";
                       print (the) x1, " kan du";
                   }
                   else print "^Du kan";
                   if (n==5) print " också";
                   print " se ";
                   WriteListFrom(child(x1),
                     ENGLISH_BIT+RECURSE_BIT+PARTINV_BIT+TERSE_BIT+CONCEAL_BIT+WORKFLAG_BIT);
                   if (x1 ~= location) ".";
                   " här.";
               7:  "Du ser inget särskilt i den riktningen.";
           }
  LookUnder: switch(n)
           {   1: "Men det är ju mörkt.";
               2: "Du hittar inget av intresse.";
           }
  Mild:           "Precis vad jag tänkte.";
  Miscellany:
           switch(n)
           {   1: "(tar bara hänsyn till de första sexton föremålen)^";
               2: "Inget att göra!";
               3: print " Du har dött ";
               4: print " Du har vunnit ";
               5: print "^Vill du BÖRJA OM, HÄMTA ett sparat spel";
                  #IFDEF DEATH_MENTION_UNDO;
                  print ", ÅNGRA ditt senaste drag";
                  #ENDIF;
                  if (TASKS_PROVIDED==0)
                      print ", visa FULL information om dina poäng";
                  if (deadflag==2 && AMUSING_PROVIDED==0)
                      print ", se några förslag på ROLIGA saker att prova";
                  " eller SLUTA?";
               6: "[Din speltolk har tyvärr inte ~ångra~.]";
               7: "~Ångra~ misslyckades.  [Det är inte alla speltolkar som har ~ångra~.]";
               8: "Skriv ett av svaren ovan.";
               9: "^Nu är det kolsvart här inne!";
              10: "Ursäkta?";
              11: "[Du kan inte ~ångra~ något som du inte har gjort!]";
              12: "[Du kan tyvärr inte ~ångra~ två gånger i rad.]";
              13: "[Senaste draget ångrat.]";
              14: "Tyvärr, det kan inte rättas till.";
              15: "Det var så lite så.";
              16: "~Hoppsan~ kan bara rätta till ett enda ord.";
              17: "Det är kolsvart, och du kan inte se någonting alls.";
              18: print "dig själv";
              19: "Lika snygg som alltid.";           
              20: "För att upprepa ett kommando som ~groda, hoppa~, skriv bara
                   ~igen~, inte ~groda, igen~.";
              21: "Det verkar inte rimligt att göra det igen.";
              22: "Du kan inte börja en mening med ett komma.";
              23: "Du verkar vilja prata med någon, men jag förstår inte vem.";
              24: "Du kan inte prata med ", (the) x1, ".";
              25: "För att prata med någon, prova ~någon, hej~ eller något liknande.";
              26: "(tar först upp ", (the) not_holding, ")";
              27: "Den meningen förstod jag inte.";
              28: print "Jag tror jag förstod ~";
              29: "Det talet förstod jag inte.";
              30: "Någon sådan ser du inte till.";
              31: "Du verkar ha sagt för lite!";
              32: print_ret (CDenEllerHonom) x1, " håller du inte i!"; ! ¤#¤ Could be rephrased to include the correct Den/Det, using ThatorThose?
              33: "Du kan inte använda flera föremål med det verbet.";
              34: "Du kan bara använda flera föremål en gång per rad.";
              35: "Jag är inte säker på vad ~", (address) pronoun_word,
                  "~ refererar till.";
              36: "Du undantog något som ändå inte var med!";
              37: "Det kan du bara göra med något levande.";
              38: "Det verbet känner jag inte igen.";
              39: "Det är inte något du har någon användning av i det här spelet.";
              40: "Du kan inte se ~", (address) pronoun_word,
                  "~ (", (the) pronoun_obj, ") just nu.";
              41: "Jag förstod inte riktigt den avslutningen.";
              42: print "Det finns ";
                  if (x1==0) print "inga";
                  else { print "bara "; LanguageNumber(x1, 0, multiple_object-->1); }
                  if (x1==1) {
                    if(multiple_object-->1 has neuter)
                      " sådant tillgängligt.";
                    " sådan tillgänglig.";
                  } else
                    " sådana tillgängliga."; ! ¤#¤ Tries to care about gender
              43: "Inget att göra!";
              44: switch(action_to_be) {
                    ##Drop, ##Insert, ##PutOn: "Du har inget att släppa!";
                    default: "Det finns inget att ta!";
                  }
              45: print "Vem menar du, ";
              46: print "Menar du ";
              47: "Tyvärr kan du bara ange ett föremål här. Exakt vilket menar du?";
              48: print "Jag antar att du menar ~"; ! ¤#¤ This message should work now
                  if (actor~=player) print (name) actor, ", ";
                  PrintCommand();
                  style bold;
                  print " någon";
                  style roman;
                  print "~, men vem?^";
              49: print "Jag antar att du menar ~";
                  if (actor~=player) print (the) actor, ", ";
                  PrintCommand();
                  style bold;
                  print " något";
                  style roman;
                  print "~, men vad?^";
!              50: print "Din poäng har just gått ";
!                  if (x1 > 0) print "upp"; else { x1 = -x1; print "ner"; }
!                  print " med ", (number) x1, " poäng";
              50: print "Du ";
                  if (x1 > 0) print "fick"; else { x1 = -x1; print "förlorade"; }
                  print " just "; 
                  LanguageNumber(x1,false,false,neuter); 
                  print " poäng";
              51: "(Eftersom något dramatiskt har hänt
                   har din sekvens av kommandon avbrutits.)";
              52: "^Skriv ett tal mellan 1 och ", x1,
                  ", 0 för att visa det här igen eller tryck RETURN.";
              53: "^[Tryck MELLANSLAG.]";
              54: "[Kommentar sparad.]";
              55: "[Kommentar INTE sparad.]";
              56: "~, men sedan tappade du bort mig.";
              57: print "?^";
           }
  NotifyOn:       "Poängmeddelanden påslaget.";
  NotifyOff:      "Poängmeddelanden avslaget.";
  Objects: switch(n)
           {   1: "Föremål du har använt:^";
               2: "Inga.";
               3: print "   (",(indefadjworn) x1,")"; ! ¤#¤ Is x1 actually set to the object# in question here? (It is now)
               4: print "   (",(indefadjheld) x1,")"; ! ¤#¤ Is x1 actually set to the object# in question here? (It is now)
               5: print "   (",(indefadjgiven) x1,")"; ! ¤#¤ Is x1 actually set to the object# in question here? (It is now)
               6: print "   (i ", (name) x1, ")";
               7: print "   (i ", (the) x1, ")";
               8: print "   (inuti ", (the) x1, ")";
               9: print "   (på ", (the) x1, ")";
              10: print "   (borta)";
           }
  Open:    switch(n)
           {   1: print_ret (CDenEllerHan) x1,
                  " kan inte öppnas.";
               2: print_ret (CDenEllerHan) x1," verkar ",(indefadjlocked) x1,".";
               3: print_ret (CDenEllerHan) x1," är redan ",(indefadjopen) x1,".";
               4: print "Du öppnar ", (the) x1, " och finner då ";
                  if (WriteListFrom(child(x1),
                      ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT)==0) "nothing.";
                  ".";
               5: "Du öppnar ", (the) x1, ".";
           }
  Order:          print_ret (The) x1," har viktigare saker för sig.";
  Places: switch (n) {
        1:  print "Du har besökt: ";
        2:  print ".^";
    }
  Pray:           "Inget direkt uppenbart händer.";
  Pronouns: switch(n)
           {   1: print "För tillfället refererar ";
               2: print "till ";
               3: print "inte till något särskilt";
               4: "inga pronomen till något alls.";
               5: ".";
           }
  Pull, Push, Turn:
           switch(n)
           {   1: print_ret (CDenEllerHan) x1, " sitter fast.";
               2: "Det misslyckas.";
               3: "Inget verkar hända.";
               4: "Det vore direkt ohyfsat.";
           }
  PushDir: switch(n)
           {   1: "Var det det bästa du kunde komma på?";
               2: "Det är ingen riktning.";
               3: "I den riktningen går det i alla fall inte.";
           }
  PutOn:   switch(n)
           {   1: "Du måste hålla i ", (the) x1,
                  " innan du kan lägga ", (DenEllerHonom) x1,
                  " på något annat.";
               2: "Du kan inte lägga något på sig självt.";
               3: "Att lägga saker på ", (the) x1, " skulle inte leda någon vart.";
               4: "Du är inte smidig nog.";
               5: "(tar först av ", (DenEllerHonom) x1, ")^";
               6: "Det finns inte plats för något mer på ", (the) x1, ".";
               7: "Gjort.";
               8: "Du placerar ", (the) x1, " på ", (the) second, ".";
           }
  Quit:    switch(n)
           {   1: print "Svara ja eller nej.";
               2: print "Är du säker på att du vill sluta? ";
           }
  Remove:  switch(n)
           {   1: print_ret (CDenEllerHan) x1, " är tyvärr in",(indefadjclosed) x1, ".";
               2: print_ret "Men ",(DenEllerHan) x1, " är inte där nu.";
               3: "Borttagen.";
           }
  Restart: switch(n)
           {   1: print "Är du säker på att du vill börja om? ";
               2: "Misslyckades.";
           }
  Restore: switch(n)
           {   1: "Hämtningen misslyckades.";
               2: "Ok.";
           }
  Rub:            "Det ger inget användbart resultat.";
  Save:    switch(n)
           {   1: "Sparningen misslyckades.";
               2: "Ok.";
           }
  Score:   switch (n) {
               1: if (deadflag) print "I det spelet fick du ";
                  else print "Du har hittills fått ihop ";
                  print score, " poäng av ", MAX_SCORE,
                  " möjliga på ", turns, " drag";
                  return;
               2: "Det finns inga poäng i detta spel.";
           }
  ScriptOn: switch(n)
           {   1: "Utskrift är redan påslaget.";
               2: "Här börjar en utskrift av";
               3: "Försöket att påbörja en utskrift misslyckades.";
           }
  ScriptOff: switch(n)
           {   1: "Utskrift är redan avslaget.";
               2: "^Här slutar utskriften.";
               3: "Försöket att avsluta utskriften misslyckades.";
           }
  Search:  switch(n)
           {   1: "Men det är ju mörkt.";
               2: "Det finns inget på ", (the) x1, ".";
               3: print "På ", (the) x1;
                  WriteListFrom(child(x1),
                      TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
                  ".";
               4: "Du hittar inget av intresse.";
               5: "Du ser inte vad som finns i ", (the) x1, ", eftersom ",
                  (DenEllerHan) x1, " är ",(indefadjclosed) x1,".";
               6: print_ret (The) x1, " är ",(indefadjempty) x1,".";
               7: print "I ", (the) x1;
                  WriteListFrom(child(x1),
                      TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
                  ".";
           }
  Set:            "Nej, du kan inte sätta ", (DenEllerHonom) x1, ".";
  SetTo:          "Nej, du kan inte sätta ", (DenEllerHonom) x1, " till något.";
  Show:    switch(n)
           {   1: "Du håller inte i ", (the) x1, ".";
               2: print (The) x1, " är inte imponera";
                  if (x1 has pluralname) "de.";
                  if (x1 has neuter) "t."; else "d.";
           }
  Sing:           "Din sångröst är inte mycket att hurra för.";
  Sleep:          "Du känner dig inte direkt sömnig.";
  Smell:          "Du känner inga oväntade lukter.";
  Sorry:          "Det är okej. För den här gången.";
  Squeeze: switch(n)
           {   1: "Tafsa inte!";
               2: "Det ger inget märkbart resultat.";
           }
  Strong:         "Riktiga äventyrare använder inte sådana ord.";
  Swim:           "Det finns inte så mycket vatten att simma i.";
  Swing:          "Det finns just inget vettigt att gunga här.";
  SwitchOn: switch(n)
           {   1: print_ret (CDenEllerHan) x1," verkar inte vara något du kan slå av och på.";
               2: print_ret (DenEllerHan) x1,
                  " är redan på.";
               3: "Du slår på ", (the) x1, ".";
           }
  SwitchOff: switch(n)
           {   1: print_ret (CDenEllerHan) x1," verkar inte vara något du kan slå av och på.";
               2: print_ret (CDenEllerHan) x1,
                  " är redan av.";
               3: "Du slår av ", (the) x1, ".";
           }
  Take:    switch(n)
           {   1: print "Tag";
                  if(noun has pluralname) "na.";
                  if(noun has neuter) "et."; else "en.";
               2: "Du är alltid självupptagen.";
               3: "Det vill ",(DenEllerHan) x1," nog inte.";
               4: print_ret "Då måste du först lämna ",(the) x1, ".";
               5: "Du har redan ", (DenEllerHonom) x1, ".";
               6: print_ret (CDenEllerHan) noun, " verkar tillhöra ", (the) x1, ".";
               7: print_ret (CDenEllerHan) noun, " verkar vara en del av ", (the) x1, ".";
               8: print_ret "Du kan inte komma åt ",(DenEllerHonom) x1, "."; ! ¤#¤ This must be modified to handle neuter correctly
               9: print_ret (The) x1, " är inte ",(indefadjopen) x1, ".";
              10: print_ret "Du kan knappast flytta ", (DenEllerHonom) x1, ".";
              11: print_ret (CDenEllerHan) x1, " sitter fast.";
              12: "Du bär redan på för mycket.";
              13: "(lägger ", (the) x1, " i ", (the) SACK_OBJECT,
                  " för att få plats)";
           }
  Taste:          "Du känner ingen oväntad smak.";
  Tell:    switch(n)
           {   1: "Du pratar lite med dig själv.";
               2: "Ingen reaktion.";
           }
  Think:          "En utmärkt idé!";
  ThrowAt: switch(n)
           {   1: "Meningslöst.";
               2: "När det väl kommer till kritan vågar du inte.";
           }
  Touch:   switch(n)
           {   1: "Bort med tassarna!";
               2: "Det känns ungefär som du hade förväntat dig.";
               3: "Om du tror att det hjälper, så visst.";
           }
  TranscribeOn:
           switch(n)
           {   1: "Transkriptionsläge är redan påslaget.";
               2: "Transkriptionsläge påslaget. ~aa~ betyder nu å, ~ae~ betyder ä
                   och ~oe~ betyder ö. Skriv ett utropstecken före varje sådan 
                   bokstavskombination som INTE ska transkriberas, som t ex i ~oeppna b!oetten~.
                   Skriv ~transkription visa~ för att få meddelande när transkription används.";
           }
  TranscribeOff:   
           switch(n)
           {   1: "Transkriptionsläge är redan avslaget.";
               2: "Transkriptionsläge avslaget.";
           }
  TranscribeShow:
           switch(n)
           {   1: "Transkriptionsläge med visning är redan påslaget.";
               2: "Transkriptionsläge med visning påslaget. ~aa~ betyder nu å, ~ae~ betyder ä
                   och ~oe~ betyder ö. Skriv ett utropstecken före varje sådan 
                   bokstavskombination som INTE ska transkriberas, som t ex i ~oeppna b!oetten~.";
           }
  Unlock:  switch(n)
           {   1: print_ret (CDenEllerHan) x1, " verkar inte vara något du kan låsa upp.";
               2: print_ret (CDenEllerHan) x1," är redan o",(indefadjlocked) x1,".";
               3: print_ret (CDenEllerHan) x1, " verkar inte passa låset.";
               4: "Du låser upp ", (the) x1, ".";
           }
  VagueGo:       "Du måste tala om i vilken kompassriktning du vill gå.";
  Verify:  switch(n)
           {   1: "Spelfilen testades och verkar vara intakt.";
               2: "Spelfilen testades men verkar inte vara intakt.
                   Det kan finnas allvarliga fel på den.";
           }
  Wait:           "Du väntar.";
  Wake:           "Den grymma sanningen är att det här inte är någon dröm.";
  WakeOther:      "Det verkar onödigt.";
  Wave:    switch(n)
           {   1: "Men du håller inte i ", (DenEllerHonom) x1, ".";
               2: "Du ser fånig ut när du viftar med ", (the) x1, ".";
           }
  WaveHands:      "Du vinkar, även om det känns lite fånigt.";
  Wear:    switch(n)
           {   1: "Du kan inte ta på dig ", (DenEllerHonom) x1, "!";
               2: "Du håller inte i ", (DenEllerHonom) x1, "!";
               3: print_ret (CDenEllerHonom) x1, " har du redan på dig!";
               4: "Du tar på dig ", (the) x1, ".";
           }
  Yes, No:        "Det var en retorisk fråga.";
];

! ==============================================================================

Constant LIBRARY_SWEDISH;       ! for dependency checking.

! ==============================================================================
