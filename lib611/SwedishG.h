! ----------------------------------------------------------------------------
!  GRAMMAR:  Grammar table entries for the standard verbs library.
!
!   Supplied for use with Inform 6 -- Release 6/11 -- Serial number 040227
!
!   Copyright Graham Nelson 1993-2004 but freely usable (see manuals)
!   Translated to Swedish by Fredrik Ramsberg 2003-2004.
!
!   This translation has a license which should always be distributed
!   along with it. It basically says that you're free to use the translation,
!   as long as you don't sell it and don't claim that you've written it.
!   You may sell games compiled using this translation though.
!
!   In your game file, Include these library files in this order:
!       Include "SweAlpha"; ! Must be included at the *very* beginning of game
!                           ! even before Story and Headline are defined
!       Include "Parser";
!       Include "VerbLib";
!       Include "SweRout";
!       Include "SwedishG";
! ==============================================================================

System_file;

#ifndef LIBRARY_SWEDISH;
  #ifdef LIBRARY_ENGLISH;
    Message "ERROR: You must use 'inform +language_name=Swedish ...' to compile.";
  #ifnot;
    Message "ERROR: Files MUST be included in this order: Parser, Verblib, SweRout, SwedishG.";
    abort;
  #endif;
#endif;

! ----------------------------------------------------------------------------
!  The "meta-verbs", commands to the game rather than in the game, come first:
! ----------------------------------------------------------------------------

Verb meta 'a//' 'avsluta' 'sluta' 'd�'
                *                                -> Quit
                * 'spela'/'spelet'               -> Quit;
Verb meta 'b�rja'
                *                                -> Restart
                * 'om'                           -> Restart;
Verb meta 'fullpo�ng' 'full'
                *                                -> FullScore
                * 'po�ng'                        -> FullScore;
Verb meta 'h�mta' 'ladda'
                * 'sparat' 'spel'                -> Restore
                * 'sparad' 'position'            -> Restore
                * 'sparning'                     -> Restore
                * 'spel'                         -> Restore
                *                                -> Restore;
Verb meta 'ingen'
                * 'utskrift'                     -> ScriptOff;
Verb meta 'inspelning'
                *                                -> CommandsOn
                * 'p�'                           -> CommandsOn
                * 'av'                           -> CommandsOff;
Verb meta 'kort' 'korta'
                *                                -> LMode3
                * 'beskrivningar'                -> LMode3;
Verb meta 'l�ngt' 'l�ng' 'l�nga'
                *                                -> LMode2
                * 'beskrivningar'                -> LMode2;
Verb meta 'meddelanden'
                * 'p�'                           -> NotifyOn
                * 'av'                           -> NotifyOff;
Verb meta 'normalt' 'normal' 'normala'
                *                                -> LMode1
                * 'beskrivningar'                -> LMode1;
Verb meta 'po�ng'
                *                                -> Score;
Verb meta 'pronomen' 'substantiv'
                *                                -> Pronouns;
Verb meta 'spara'
                * 'spel'                         -> Save
                * 'spelet'                       -> Save
                *                                -> Save;
Verb meta 'transkribera' 'transkription'
                *                                -> TranscribeOn
                * 'p�'                           -> TranscribeOn
                * 'visa'/'visning'               -> TranscribeShow
                * 'av'                           -> TranscribeOff;
Verb meta 'uppspelning'
                *                                -> CommandsRead;
Verb meta 'utskrift'
                *                                -> ScriptOn
                * 'av'                           -> ScriptOff
                * 'p�'                           -> ScriptOn;
Verb meta 'verifiera'
                *                                -> Verify;
Verb meta 'version'
                *                                -> Version;




#IFNDEF NO_PLACES;
Verb meta 'objekt' 'saker' 'prylar'
                *                                -> Objects;
Verb meta 'platser' 'rum' 'st�llen'
                *                                -> Places;
#ENDIF;

! ----------------------------------------------------------------------------
!  Debugging grammar
! ----------------------------------------------------------------------------

#Ifdef DEBUG;
Verb meta 'actions'
    *                                           -> ActionsOn
    * 'on'                                      -> ActionsOn
    * 'off'                                     -> ActionsOff;
Verb meta 'changes'
    *                                           -> ChangesOn
    * 'on'                                      -> ChangesOn
    * 'off'                                     -> ChangesOff;
Verb meta 'gonear'
    * noun                                      -> Gonear;
Verb meta 'goto'
    * number                                    -> Goto;
Verb meta 'random'
    *                                           -> Predictable;
Verb meta 'routines' 'messages'
    *                                           -> RoutinesOn
    * 'on'                                      -> RoutinesOn
    * 'off'                                     -> RoutinesOff;
Verb meta 'scope'
    *                                           -> Scope
    * noun                                      -> Scope;
Verb meta 'showobj'
    *                                           -> Showobj
    * number                                    -> Showobj
    * multi                                     -> Showobj;
Verb meta 'showverb'
    * special                                   -> Showverb;
Verb meta 'timers' 'daemons'
    *                                           -> TimersOn
    * 'on'                                      -> TimersOn
    * 'off'                                     -> TimersOff;
Verb meta 'trace'
    *                                           -> TraceOn
    * number                                    -> TraceLevel
    * 'on'                                      -> TraceOn
    * 'off'                                     -> TraceOff;
Verb meta 'abstract'
    * noun 'to' noun                            -> XAbstract;
Verb meta 'purloin'
    * multi                                     -> XPurloin;
Verb meta 'tree'
    *                                           -> XTree
    * noun                                      -> XTree;
Verb meta '�rnkoll' '�rnkolla'
    *                                           -> CheckGame;


#Ifdef TARGET_GLULX;
Verb meta 'glklist'
    *                                           -> Glklist;
#Endif; ! TARGET_

#Endif; ! DEBUG

! ----------------------------------------------------------------------------
!  And now the game verbs.
! ----------------------------------------------------------------------------

[ Exitable ;
  if(player in noun) rtrue;
  rfalse;
];
 
[ ADirection; if (noun in compass) rtrue; rfalse; ];
                                                 

Verb 'attackera' 'anfall' 'krossa' 'kn�ck' 'd�da'
     'f�rst�r' 'bryt' 'm�rda' 'tortera' 'nita'   
                * noun                                      -> Attack;
Verb 'be'                                        
                *                                           -> Pray
                * 'att' 'f�' noun 'av' creature             -> AskFor
                * creature 'om' noun                        -> AskFor;
Verb 'ber�tta' 'f�rklara'                                   
                * 'f�r' creature 'om' topic                 -> Tell
                * 'om' topic 'f�r' creature                 -> Tell reverse;
Verb 'besk�r'                                               
                * noun                                      -> Cut;
Verb 'betala' 'erbjud'                           
                * held 'till' creature                      -> Give
                * creature held                             -> Give reverse;
Verb 'bind' 'f�st'                                          
                * noun                                      -> Tie
                * 'fast' noun 'i//' noun                    -> Tie
                * noun 'i//' noun                           -> Tie;
Verb 'bl�s'                                                 
                * 'p�'/'i//' held                           -> Blow;
Verb 'br�nn' 't�nd'                                         
                * noun                                      -> Burn
                * 'p�' noun                                 -> Burn
                * 'p�' noun 'med' held                      -> Burn
                * noun 'med' held                           -> Burn;
Verb 'b�nd' 'forcera'
                * noun 'med' held                           -> Unlock
                * 'upp' noun 'med' held                     -> Unlock;
Verb 'b�r'                                       
                * clothing                                  -> Wear
                * noun                                      -> Take;
Verb 'dra' 'drag'                                           
                * 'i//' noun                                -> Pull
                * noun                                      -> Pull;
Verb 'drick'                                                
                * noun                                      -> Drink
                * 'ur' noun                                 -> Drink;
Verb 'dumpa' 'avyttra'                           
                * multiheld                                 -> Drop
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * multiexcept 'p�'/'ovanp�' noun            -> PutOn
                * multiexcept 'uppe' 'p�' noun              -> PutOn;
Verb 'flytta'
                * noun                                      -> Push
                * 'p�' noun                                 -> Push
                * noun noun                                 -> PushDir
                * noun 'till' noun                          -> Transfer;
Verb 'fr�ga'                                                
                * creature 'om' topic                       -> Ask;
Verb 'fyll'                                                 
                * noun                                      -> Fill
                * 'p�'/'upp' noun                           -> Fill;
Verb 'ge' 'giv'                                  
                * held 'till' creature                      -> Give
                * 'bort' held 'till' creature               -> Give
                * creature held                             -> Give reverse;
Verb 'genoms�k'                                             
                * noun                                      -> Search;
Verb 'gnid' 'polera' 'damma' 'stryk' 'skrubba'              
                * noun                                      -> Rub
                * 'av'/'p�' noun                            -> Rub;
Verb 'gr�v'     * noun                                      -> Dig
                * 'i//'/'upp' noun 'med' held               -> Dig;
Verb 'gunga'                                                
                * noun                                      -> Swing
                * 'p�' noun                                 -> Swing;
Verb 'g�' 'spring'
                *                                           -> VagueGo
                * 'in'                                      -> GoIn
                * 'ut'                                      -> Exit
                * noun=ADirection                           -> Go
                * '�t'/'mot' noun=ADirection                -> Go
                * 'upp' 'fr�n' noun                         -> Exit
                * noun                                      -> Enter
                * 'p�' noun                                 -> Enter
                * 'upp' 'p�' noun                           -> Enter
                * 'ut'/'in' 'i//'/'genom'/'igenom' noun     -> Enter
                * 'genom'/'igenom' noun                     -> Enter
                * 'ur'/'av' noun                            -> Exit
                * 'ut' 'ur' noun                            -> Exit
                * 'ned'/'ner' 'fr�n' noun                   -> Exit;
Verb 'kliv' 'stig'
                * 'p�' noun                                 -> Enter
                * 'upp'                                     -> Exit
                * 'upp' 'fr�n' noun                         -> Exit
                * 'in'                                      -> GoIn
                * 'ut'                                      -> Exit
                * 'upp' 'p�' noun                           -> Enter
                * 'in' 'i//'/'genom'/'igenom' noun          -> Enter
                * 'ur'/'av' noun                            -> Exit
                * 'ut' 'ur' noun                            -> Exit
                * 'ned'/'ner' 'fr�n' noun                   -> Exit;
Verb 'hoppa'                                                
                *                                           -> Jump
                * '�ver' noun                               -> JumpOver;
Verb 'in'                                                   
                *                                           -> GoIn;
Verb 'ja' 'j//'                                             
                *                                           -> Yes;
Verb 'kasta' 'sl�ng'                             
                * multiheld                                 -> Drop
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * 'in'/'ner'/'ned' multiexcept 'i//'/'inuti' noun   
                                                            -> Insert
                * 'in'/'ner'/'ned' multiexcept 'inne' 'i' noun
                                                            -> Insert
!                * multiexcept 'p�' noun                     -> PutOn
!                * multiexcept 'ovanp�' noun                 -> PutOn
!                * multiexcept 'uppe' 'p�' noun              -> PutOn
                * 'upp'/'ner'/'ned' multiexcept 'p�'/'ovanp�' noun
                                                            -> PutOn
                * 'upp'/'ner'/'ned' multiexcept 'uppe' 'p�' noun
                                                            -> PutOn
                * held 'p�'/'mot' noun                      -> ThrowAt;
Verb 'kl�m'                                                 
                * noun                                      -> Squeeze
                * 'p�' noun                                 -> Squeeze;
Verb 'kl�ttra'
                * 'p�'/'�ver'/'uppf�r'/'i' noun             -> Climb
                * 'ut'/'av'/'ner'/'ned'                     -> Exit
                * 'av'/'ner'/'ned' 'fr�n' noun              -> Exit
                * 'upp' 'p�' noun                           -> Climb
                * 'ut'/'in' 'i//'/'genom'/'igenom' noun     -> Enter
                * 'genom'/'igenom' noun                     -> Enter;
Verb 'korsa'                                                
                * noun                                      -> Enter;
Verb 'krama' 'omfamna'                                      
                * creature                                  -> Kiss
                * noun                                      -> Squeeze;
Verb 'kyss' 'pussa'                                         
                * creature                                  -> Kiss;
Verb 'k�p' 'inhandla' 'handla'                              
                * noun                                      -> Buy;
Verb 'ledsen' 'urs�kta' 'f�rl�t' 'beklagar'                 
                *                                           -> Sorry;
Verb 'lista' 'l//'                                          
                *                                           -> Inv
                * 'tillh�righeter'/'�godelar'               -> Inv
                * 'mina' 'tillh�righeter'/'�godelar'/'saker'
                                                            -> Inv
                * 'l�ng'                                    -> InvTall
                * 'bred'                                    -> InvWide;
Verb 'lukta' 'sniffa'                                       
                *                                           -> Smell
                * 'p�'/'i//' noun                           -> Smell;
Verb 'lyssna' 'h�r'                                         
                *                                           -> Listen
                * 'p�' noun                                 -> Listen;
Verb 'l�gg'
                * 'mig'/'dig' 'p�'/'i//' noun               -> Enter
                * 'mig'/'dig' 'uppe' 'p�'/'i//' noun        -> Enter
                * multiexcept 'inuti'/'i//' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * multiexcept 'p�'/'ovanp�' noun            -> PutOn
                * multiexcept 'uppe' 'p�' noun              -> PutOn
                * 'ned'/'ner'/'bort' multiheld              -> Drop
                * 'ned'/'ner'/'in' multiheld 'i//'/'inuti' noun  
                                                             -> Insert
                * 'ned'/'ner'/'in' multiheld 'inne' 'i//' noun 
                                                            -> Insert
                * 'ned'/'ner'/'upp' multiexcept 'p�'/'ovanp�' noun
                                                            -> PutOn
                * 'ned'/'ner'/'upp' multiexcept 'uppe' 'p�' noun
                                                            -> PutOn
                * 'ifr�n' 'dig'/'mig' multiheld             -> Drop;
                                                 
Verb 'l�mna'    * noun=Exitable                             -> Exit
                * multiheld                                 -> Drop
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * multiexcept 'p�'/'ovanp�' noun            -> PutOn
                * multiexcept 'uppe' 'p�' noun              -> PutOn;
Verb 'l�s'                                                  
                * noun                                      -> Examine
                * 'i//'/'p�' noun                           -> Examine
                * 'om' topic 'i//' noun                     -> Consult;
Verb 'l�s'                                       
                * noun 'med' held                           -> Lock
                * 'upp' noun 'med' held                     -> Unlock;
Verb 'nedrans' 'attans' 'j�rnv�gar' 'sjutton'               
     'tusan' 'dubbeltusan' 'j�rnspikar' 'b�veln'            
     'rackarns' 'fy'                                        
                *                                           -> Mild
                * topic                                     -> Mild;
Verb 'nej'                                                  
                *                                           -> No;
Verb 'placera'
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * multiexcept 'p�'/'ovanp�' noun            -> PutOn
                * multiexcept 'uppe' 'p�' noun              -> PutOn;
Verb 'res'
                * 'p�' 'mig'/'dig'                          -> Exit
                * 'mig'/'dig'                               -> Exit
                * 'mig'/'dig' 'upp'                         -> Exit
                * 'mig'/'dig' 'fr�n' noun                   -> Exit;
Verb 'r�r'                                                  
                * noun                                      -> Touch
                * 'p�'/'vid' noun                           -> Touch;
Verb 'simma' 'dyk'                                          
                *                                           -> Swim;
Verb 'sitt' 'ligg'                                          
                * 'p�' noun                                 -> Enter
                * 'uppe'/'upp' 'p�' noun                    -> Enter
                * 'inne' 'i//' noun                         -> Enter
                * 'i//'/'inuti'/'p�' noun                   -> Enter;
Verb 'sjung' 'tralla' 'nynna' 'jollra'                      
                *                                           -> Sing;
Verb 'skit' 'satan' 'j�vlar' 'helvete' 'fan'                
                *                                           -> Strong
                * topic                                     -> Strong;
Verb 'sk�r'                                                 
                * noun                                      -> Cut
                * 'av'/'upp'/'ner'/'i//' noun               -> Cut;
Verb 'sl�'                                                  
                * 'upp' topic 'i//' noun                    -> Consult
                * noun                                      -> Attack
                * 'ner'/'s�nder' noun                       -> Attack
                * 'till'/'p�' switchable                    -> SwitchOn
                * 'av'/'fr�n' switchable                    -> SwitchOff
                * 'till'/'p�' noun                          -> Attack;
Verb 'sl�pp'                                     
                * multiheld                                 -> Drop
                * 'ner'/'ned' multiexcept 'p�'/'ovanp�' noun -> PutOn
                * 'ner'/'ned' multiexcept 'uppe' 'p�' noun  -> PutOn
                * 'ner'/'ned'/'in' multiexcept 'i//'/'inuti' noun
                                                            -> Insert
                * 'ner'/'ned'/'in' multiexcept 'inne' 'i//' noun
                                                            -> Insert
                * multiexcept 'p�'/'ovanp�' noun            -> PutOn
                * multiexcept 'uppe' 'p�' noun              -> PutOn
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert;
Verb 'smaka'                                                
                * noun                                      -> Taste
                * 'p�' noun                                 -> Taste;
Verb 'smek' 'k�nn' 'h�ll'                                   
                * noun                                      -> Touch
                * 'p�' noun                                 -> Touch;
Verb 'snurra' 'skruva' 'vrid'
                * noun                                      -> Turn                                     
                * 'p�'/'av' noun                            -> Turn;
Verb 'sov' 'vila'                                           
                *                                           -> Sleep;
Verb "starta"
                * noun                                      -> Switchon;
Verb 'st�'                                                  
                *                                           -> Exit
                * 'upp'                                     -> Exit
                * 'p�' noun                                 -> Enter
                * 'i' noun                                  -> Enter;
Verb 'st�ll'
                * 'mig'/'dig' 'p�'/'i//' noun               -> Enter
                * 'mig'/'dig' 'upp'                         -> Exit
                * multiexcept 'p�'/'ovanp�' noun            -> PutOn
                * multiexcept 'uppe' 'p�' noun              -> PutOn
                * 'ner'/'ned' multiheld                     -> Drop
                * 'ner'/'ned'/'upp' multiexcept 'p�'/'ovanp�' noun
                                                            -> PutOn
                * 'ner'/'ned'/'upp' multiexcept 'uppe' 'p�' noun
                                                            -> PutOn
                * 'ner'/'ned'/'in' multiexcept 'i//'/'inuti' noun
                                                            -> Insert
                * 'ner'/'ned'/'in' multiexcept 'inne' 'i//' noun
                                                            -> Insert
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * noun                                      -> Set
                * 'in' noun                                 -> Set
                * 'in' noun 'p�' special                    -> SetTo;
Verb 'st�ng'                                                
                * noun                                      -> Close
                * 'till' noun                               -> Close
                * 'av' noun                                 -> SwitchOff;
Verb 'svara'                                                
                * creature topic                            -> Answer;
Verb 'sv�lj'                                                
                * noun                                      -> Drink;
Verb 's�g' 'skrik'                                          
                * topic 'till' creature                     -> Answer;
Verb 's�tt'
                * 'mig'/'dig' 'p�'/'i//' noun               -> Enter
                * 'mig'/'dig' 'uppe' 'p�'/'i//' noun        -> Enter
                * 'fast' noun 'i//' noun                    -> Tie
                * multiexcept 'p�'/'ovanp�' noun            -> PutOn
                * multiexcept 'uppe' 'p�' noun              -> PutOn
                * 'ner'/'ned' multiheld                     -> Drop
                * 'ner'/'ned'/'upp' multiexcept 'p�'/'ovanp�' noun
                                                            -> PutOn
                * 'ner'/'ned'/'upp' multiexcept 'uppe' 'p�' noun
                                                            -> PutOn
                * 'ner'/'ned'/'in' multiexcept 'i//'/'inuti' noun
                                                            -> Insert
                * 'ner'/'ned'/'in' multiexcept 'inne' 'i//' noun
                                                            -> Insert
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * 'p�' switchable                           -> SwitchOn
                * 'p�' clothing                             -> Wear
                * 'p�' creature                             -> Kiss
                * noun                                      -> Set
                * noun 'till'/'p�' special                  -> SetTo;
Verb 's�k'                                                  
                * 'igenom'/'i//' noun                       -> Search;
Verb 'ta' 'plocka' 'tag'
                * multi                                     -> Take
                * 'tag' 'i//' multi                         -> Take
                * 'upp'/'fram' multi                        -> Take
                * 'av' 'mig'/'dig' noun                     -> Disrobe ! �#� This causes trouble because "mig" also refers to player
                * 'av' worn                                 -> Disrobe
                * multiinside 'fr�n'/'ur'/'i//' noun        -> Remove
                * 'upp'/'fram'/'ut'/'ur'/'bort' multiinside 'i//'/'fr�n'/'ur' noun
                                                            -> Remove
                * 'p�' 'mig'/'dig' noun                     -> Wear ! �#� This causes trouble because "mig" also refers to player
                * 'p�' clothing                             -> Wear
                * 'p�' noun                                 -> Touch;
Verb 'tappa'                                     
                * noun                                      -> Drop
                * 'av'/'ur'/'ut' noun                       -> Empty
                * 'av'/'ur'/'ut' noun 'i//'/'inuti'/'ovanp�'/'p�' noun
                                                            -> EmptyT;
Verb 'titta' 'se' 't//'                                     
                *                                           -> Look
                * noun=ADirection                           -> Examine
                * '�t'/'mot' noun=ADirection                -> Examine
                * 'p�' noun                                 -> Examine
                * 'n�rmare' 'p�' noun                       -> Examine
                * 'i//'/'inuti'/'genom'/'igenom' noun       -> Search
                * 'in'/'inne' 'i//' noun                    -> Search
                * 'under' noun                              -> LookUnder;
Verb 'tryck' 'knuffa' 'putta'                               
                * noun                                      -> Push
                * 'p�'/'till' noun                          -> Push
                * noun noun                                 -> PushDir
                * noun 'till' noun                          -> Transfer;
Verb 't�nk'                                                 
                *                                           -> Think;
Verb 't�m'                                       
                * noun                                      -> Empty
                * 'ut'/'ur' noun                            -> Empty
                * 'ut'/'ur' noun 'i//'/'inuti'/'p�'/'ovanp�' noun
                                                            -> EmptyT;
Verb 'unders�k' 'x//'                                       
                * noun                                      -> Examine;
Verb 'ut'                                                   
                *                                           -> Exit
                * 'ur' noun                                 -> Exit;
Verb 'vakna'                                                
                *                                           -> Wake
                * 'upp'/'till'                              -> Wake;
Verb 'vifta' 'vinka'                                        
                *                                           -> WaveHands
                * 'med' noun                                -> Wave;
Verb 'visa'                                                 
                * creature held                             -> Show reverse
                * 'upp' held 'f�r' creature                 -> Show
                * held 'f�r' creature                       -> Show;
Verb 'v�ck'                                                 
                * creature                                  -> WakeOther
                * 'upp' creature                            -> WakeOther;
Verb 'v�nd' 'rotera'                                        
                * noun                                      -> Turn
                * 'runt'/'p�' noun                          -> Turn;
Verb 'v�nta' 'z//'                                          
                *                                           -> Wait;
Verb '�t'                                                   
                * 'upp' held                                -> Eat
                * held                                      -> Eat;
Verb '�ppna'                                                
                * noun                                      -> Open
                * noun 'med' held                           -> Unlock;
                                                            
                                                 
! ----------------------------------------------------------------------------
!  Final task: provide trivial routines if the user hasn't already:
! ----------------------------------------------------------------------------
#Stub TimePasses      0;                         
#Stub Amusing         0;                         
#Stub DeathMessage    0;                         
#Stub DarkToDark      0;                         
#Stub NewRoom         0;                         
#Stub LookRoutine     0;                         
#Stub AfterLife       0;                         
#Stub GamePreRoutine  0;                         
#Stub GamePostRoutine 0;                         
#Stub AfterPrompt     0;                         
#Stub BeforeParsing   0;                         
#Stub PrintTaskName   1;                         
#Stub InScope         1;                         
#Stub UnknownVerb     1;                         
#Stub PrintVerb       1;                         
#Stub ParserError     1;                         
#Stub ParseNumber     2;                         
#Stub ChooseObjects   2;                         
                                                 
#ifdef TARGET_GLULX;                             
#Stub IdentifyGlkObject 4;                       
#Stub HandleGlkEvent  2;                         
#Stub InitGlkWindow   1;                         
#endif; ! TARGET_GLULX                           
                                                 
#IFNDEF PrintRank;                               
Constant Make__PR;                               
#ENDIF;                                          
#IFDEF Make__PR;                                 
[ PrintRank; "."; ];                             
#ENDIF;                                          
#IFNDEF ParseNoun;                               
Constant Make__PN;                               
#ENDIF;                                          
#IFDEF Make__PN;                                 
[ ParseNoun obj; obj=obj; return -1; ];          
#ENDIF;                                          
#Default Story 0;                                
#Default Headline 0;                             
#IFDEF INFIX;                                    
#Include "infix";                                
#ENDIF;                                          
! ==============================================================================

Constant LIBRARY_GRAMMAR;       ! for dependency checking

! ==============================================================================
