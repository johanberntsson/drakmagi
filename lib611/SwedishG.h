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

Verb meta 'a//' 'avsluta' 'sluta' 'dö'
                *                                -> Quit
                * 'spela'/'spelet'               -> Quit;
Verb meta 'börja'
                *                                -> Restart
                * 'om'                           -> Restart;
Verb meta 'fullpoäng' 'full'
                *                                -> FullScore
                * 'poäng'                        -> FullScore;
Verb meta 'hämta' 'ladda'
                * 'sparat' 'spel'                -> Restore
                * 'sparad' 'position'            -> Restore
                * 'sparning'                     -> Restore
                * 'spel'                         -> Restore
                *                                -> Restore;
Verb meta 'ingen'
                * 'utskrift'                     -> ScriptOff;
Verb meta 'inspelning'
                *                                -> CommandsOn
                * 'på'                           -> CommandsOn
                * 'av'                           -> CommandsOff;
Verb meta 'kort' 'korta'
                *                                -> LMode3
                * 'beskrivningar'                -> LMode3;
Verb meta 'långt' 'lång' 'långa'
                *                                -> LMode2
                * 'beskrivningar'                -> LMode2;
Verb meta 'meddelanden'
                * 'på'                           -> NotifyOn
                * 'av'                           -> NotifyOff;
Verb meta 'normalt' 'normal' 'normala'
                *                                -> LMode1
                * 'beskrivningar'                -> LMode1;
Verb meta 'poäng'
                *                                -> Score;
Verb meta 'pronomen' 'substantiv'
                *                                -> Pronouns;
Verb meta 'spara'
                * 'spel'                         -> Save
                * 'spelet'                       -> Save
                *                                -> Save;
Verb meta 'transkribera' 'transkription'
                *                                -> TranscribeOn
                * 'på'                           -> TranscribeOn
                * 'visa'/'visning'               -> TranscribeShow
                * 'av'                           -> TranscribeOff;
Verb meta 'uppspelning'
                *                                -> CommandsRead;
Verb meta 'utskrift'
                *                                -> ScriptOn
                * 'av'                           -> ScriptOff
                * 'på'                           -> ScriptOn;
Verb meta 'verifiera'
                *                                -> Verify;
Verb meta 'version'
                *                                -> Version;




#IFNDEF NO_PLACES;
Verb meta 'objekt' 'saker' 'prylar'
                *                                -> Objects;
Verb meta 'platser' 'rum' 'ställen'
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
Verb meta 'örnkoll' 'örnkolla'
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
                                                 

Verb 'attackera' 'anfall' 'krossa' 'knäck' 'döda'
     'förstör' 'bryt' 'mörda' 'tortera' 'nita'   
                * noun                                      -> Attack;
Verb 'be'                                        
                *                                           -> Pray
                * 'att' 'få' noun 'av' creature             -> AskFor
                * creature 'om' noun                        -> AskFor;
Verb 'berätta' 'förklara'                                   
                * 'för' creature 'om' topic                 -> Tell
                * 'om' topic 'för' creature                 -> Tell reverse;
Verb 'beskär'                                               
                * noun                                      -> Cut;
Verb 'betala' 'erbjud'                           
                * held 'till' creature                      -> Give
                * creature held                             -> Give reverse;
Verb 'bind' 'fäst'                                          
                * noun                                      -> Tie
                * 'fast' noun 'i//' noun                    -> Tie
                * noun 'i//' noun                           -> Tie;
Verb 'blås'                                                 
                * 'på'/'i//' held                           -> Blow;
Verb 'bränn' 'tänd'                                         
                * noun                                      -> Burn
                * 'på' noun                                 -> Burn
                * 'på' noun 'med' held                      -> Burn
                * noun 'med' held                           -> Burn;
Verb 'bänd' 'forcera'
                * noun 'med' held                           -> Unlock
                * 'upp' noun 'med' held                     -> Unlock;
Verb 'bär'                                       
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
                * multiexcept 'på'/'ovanpå' noun            -> PutOn
                * multiexcept 'uppe' 'på' noun              -> PutOn;
Verb 'flytta'
                * noun                                      -> Push
                * 'på' noun                                 -> Push
                * noun noun                                 -> PushDir
                * noun 'till' noun                          -> Transfer;
Verb 'fråga'                                                
                * creature 'om' topic                       -> Ask;
Verb 'fyll'                                                 
                * noun                                      -> Fill
                * 'på'/'upp' noun                           -> Fill;
Verb 'ge' 'giv'                                  
                * held 'till' creature                      -> Give
                * 'bort' held 'till' creature               -> Give
                * creature held                             -> Give reverse;
Verb 'genomsök'                                             
                * noun                                      -> Search;
Verb 'gnid' 'polera' 'damma' 'stryk' 'skrubba'              
                * noun                                      -> Rub
                * 'av'/'på' noun                            -> Rub;
Verb 'gräv'     * noun                                      -> Dig
                * 'i//'/'upp' noun 'med' held               -> Dig;
Verb 'gunga'                                                
                * noun                                      -> Swing
                * 'på' noun                                 -> Swing;
Verb 'gå' 'spring'
                *                                           -> VagueGo
                * 'in'                                      -> GoIn
                * 'ut'                                      -> Exit
                * noun=ADirection                           -> Go
                * 'åt'/'mot' noun=ADirection                -> Go
                * 'upp' 'från' noun                         -> Exit
                * noun                                      -> Enter
                * 'på' noun                                 -> Enter
                * 'upp' 'på' noun                           -> Enter
                * 'ut'/'in' 'i//'/'genom'/'igenom' noun     -> Enter
                * 'genom'/'igenom' noun                     -> Enter
                * 'ur'/'av' noun                            -> Exit
                * 'ut' 'ur' noun                            -> Exit
                * 'ned'/'ner' 'från' noun                   -> Exit;
Verb 'kliv' 'stig'
                * 'på' noun                                 -> Enter
                * 'upp'                                     -> Exit
                * 'upp' 'från' noun                         -> Exit
                * 'in'                                      -> GoIn
                * 'ut'                                      -> Exit
                * 'upp' 'på' noun                           -> Enter
                * 'in' 'i//'/'genom'/'igenom' noun          -> Enter
                * 'ur'/'av' noun                            -> Exit
                * 'ut' 'ur' noun                            -> Exit
                * 'ned'/'ner' 'från' noun                   -> Exit;
Verb 'hoppa'                                                
                *                                           -> Jump
                * 'över' noun                               -> JumpOver;
Verb 'in'                                                   
                *                                           -> GoIn;
Verb 'ja' 'j//'                                             
                *                                           -> Yes;
Verb 'kasta' 'släng'                             
                * multiheld                                 -> Drop
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * 'in'/'ner'/'ned' multiexcept 'i//'/'inuti' noun   
                                                            -> Insert
                * 'in'/'ner'/'ned' multiexcept 'inne' 'i' noun
                                                            -> Insert
!                * multiexcept 'på' noun                     -> PutOn
!                * multiexcept 'ovanpå' noun                 -> PutOn
!                * multiexcept 'uppe' 'på' noun              -> PutOn
                * 'upp'/'ner'/'ned' multiexcept 'på'/'ovanpå' noun
                                                            -> PutOn
                * 'upp'/'ner'/'ned' multiexcept 'uppe' 'på' noun
                                                            -> PutOn
                * held 'på'/'mot' noun                      -> ThrowAt;
Verb 'kläm'                                                 
                * noun                                      -> Squeeze
                * 'på' noun                                 -> Squeeze;
Verb 'klättra'
                * 'på'/'över'/'uppför'/'i' noun             -> Climb
                * 'ut'/'av'/'ner'/'ned'                     -> Exit
                * 'av'/'ner'/'ned' 'från' noun              -> Exit
                * 'upp' 'på' noun                           -> Climb
                * 'ut'/'in' 'i//'/'genom'/'igenom' noun     -> Enter
                * 'genom'/'igenom' noun                     -> Enter;
Verb 'korsa'                                                
                * noun                                      -> Enter;
Verb 'krama' 'omfamna'                                      
                * creature                                  -> Kiss
                * noun                                      -> Squeeze;
Verb 'kyss' 'pussa'                                         
                * creature                                  -> Kiss;
Verb 'köp' 'inhandla' 'handla'                              
                * noun                                      -> Buy;
Verb 'ledsen' 'ursäkta' 'förlåt' 'beklagar'                 
                *                                           -> Sorry;
Verb 'lista' 'l//'                                          
                *                                           -> Inv
                * 'tillhörigheter'/'ägodelar'               -> Inv
                * 'mina' 'tillhörigheter'/'ägodelar'/'saker'
                                                            -> Inv
                * 'lång'                                    -> InvTall
                * 'bred'                                    -> InvWide;
Verb 'lukta' 'sniffa'                                       
                *                                           -> Smell
                * 'på'/'i//' noun                           -> Smell;
Verb 'lyssna' 'hör'                                         
                *                                           -> Listen
                * 'på' noun                                 -> Listen;
Verb 'lägg'
                * 'mig'/'dig' 'på'/'i//' noun               -> Enter
                * 'mig'/'dig' 'uppe' 'på'/'i//' noun        -> Enter
                * multiexcept 'inuti'/'i//' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * multiexcept 'på'/'ovanpå' noun            -> PutOn
                * multiexcept 'uppe' 'på' noun              -> PutOn
                * 'ned'/'ner'/'bort' multiheld              -> Drop
                * 'ned'/'ner'/'in' multiheld 'i//'/'inuti' noun  
                                                             -> Insert
                * 'ned'/'ner'/'in' multiheld 'inne' 'i//' noun 
                                                            -> Insert
                * 'ned'/'ner'/'upp' multiexcept 'på'/'ovanpå' noun
                                                            -> PutOn
                * 'ned'/'ner'/'upp' multiexcept 'uppe' 'på' noun
                                                            -> PutOn
                * 'ifrån' 'dig'/'mig' multiheld             -> Drop;
                                                 
Verb 'lämna'    * noun=Exitable                             -> Exit
                * multiheld                                 -> Drop
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * multiexcept 'på'/'ovanpå' noun            -> PutOn
                * multiexcept 'uppe' 'på' noun              -> PutOn;
Verb 'läs'                                                  
                * noun                                      -> Examine
                * 'i//'/'på' noun                           -> Examine
                * 'om' topic 'i//' noun                     -> Consult;
Verb 'lås'                                       
                * noun 'med' held                           -> Lock
                * 'upp' noun 'med' held                     -> Unlock;
Verb 'nedrans' 'attans' 'järnvägar' 'sjutton'               
     'tusan' 'dubbeltusan' 'järnspikar' 'böveln'            
     'rackarns' 'fy'                                        
                *                                           -> Mild
                * topic                                     -> Mild;
Verb 'nej'                                                  
                *                                           -> No;
Verb 'placera'
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * multiexcept 'på'/'ovanpå' noun            -> PutOn
                * multiexcept 'uppe' 'på' noun              -> PutOn;
Verb 'res'
                * 'på' 'mig'/'dig'                          -> Exit
                * 'mig'/'dig'                               -> Exit
                * 'mig'/'dig' 'upp'                         -> Exit
                * 'mig'/'dig' 'från' noun                   -> Exit;
Verb 'rör'                                                  
                * noun                                      -> Touch
                * 'på'/'vid' noun                           -> Touch;
Verb 'simma' 'dyk'                                          
                *                                           -> Swim;
Verb 'sitt' 'ligg'                                          
                * 'på' noun                                 -> Enter
                * 'uppe'/'upp' 'på' noun                    -> Enter
                * 'inne' 'i//' noun                         -> Enter
                * 'i//'/'inuti'/'på' noun                   -> Enter;
Verb 'sjung' 'tralla' 'nynna' 'jollra'                      
                *                                           -> Sing;
Verb 'skit' 'satan' 'jävlar' 'helvete' 'fan'                
                *                                           -> Strong
                * topic                                     -> Strong;
Verb 'skär'                                                 
                * noun                                      -> Cut
                * 'av'/'upp'/'ner'/'i//' noun               -> Cut;
Verb 'slå'                                                  
                * 'upp' topic 'i//' noun                    -> Consult
                * noun                                      -> Attack
                * 'ner'/'sönder' noun                       -> Attack
                * 'till'/'på' switchable                    -> SwitchOn
                * 'av'/'från' switchable                    -> SwitchOff
                * 'till'/'på' noun                          -> Attack;
Verb 'släpp'                                     
                * multiheld                                 -> Drop
                * 'ner'/'ned' multiexcept 'på'/'ovanpå' noun -> PutOn
                * 'ner'/'ned' multiexcept 'uppe' 'på' noun  -> PutOn
                * 'ner'/'ned'/'in' multiexcept 'i//'/'inuti' noun
                                                            -> Insert
                * 'ner'/'ned'/'in' multiexcept 'inne' 'i//' noun
                                                            -> Insert
                * multiexcept 'på'/'ovanpå' noun            -> PutOn
                * multiexcept 'uppe' 'på' noun              -> PutOn
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert;
Verb 'smaka'                                                
                * noun                                      -> Taste
                * 'på' noun                                 -> Taste;
Verb 'smek' 'känn' 'håll'                                   
                * noun                                      -> Touch
                * 'på' noun                                 -> Touch;
Verb 'snurra' 'skruva' 'vrid'
                * noun                                      -> Turn                                     
                * 'på'/'av' noun                            -> Turn;
Verb 'sov' 'vila'                                           
                *                                           -> Sleep;
Verb "starta"
                * noun                                      -> Switchon;
Verb 'stå'                                                  
                *                                           -> Exit
                * 'upp'                                     -> Exit
                * 'på' noun                                 -> Enter
                * 'i' noun                                  -> Enter;
Verb 'ställ'
                * 'mig'/'dig' 'på'/'i//' noun               -> Enter
                * 'mig'/'dig' 'upp'                         -> Exit
                * multiexcept 'på'/'ovanpå' noun            -> PutOn
                * multiexcept 'uppe' 'på' noun              -> PutOn
                * 'ner'/'ned' multiheld                     -> Drop
                * 'ner'/'ned'/'upp' multiexcept 'på'/'ovanpå' noun
                                                            -> PutOn
                * 'ner'/'ned'/'upp' multiexcept 'uppe' 'på' noun
                                                            -> PutOn
                * 'ner'/'ned'/'in' multiexcept 'i//'/'inuti' noun
                                                            -> Insert
                * 'ner'/'ned'/'in' multiexcept 'inne' 'i//' noun
                                                            -> Insert
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * noun                                      -> Set
                * 'in' noun                                 -> Set
                * 'in' noun 'på' special                    -> SetTo;
Verb 'stäng'                                                
                * noun                                      -> Close
                * 'till' noun                               -> Close
                * 'av' noun                                 -> SwitchOff;
Verb 'svara'                                                
                * creature topic                            -> Answer;
Verb 'svälj'                                                
                * noun                                      -> Drink;
Verb 'säg' 'skrik'                                          
                * topic 'till' creature                     -> Answer;
Verb 'sätt'
                * 'mig'/'dig' 'på'/'i//' noun               -> Enter
                * 'mig'/'dig' 'uppe' 'på'/'i//' noun        -> Enter
                * 'fast' noun 'i//' noun                    -> Tie
                * multiexcept 'på'/'ovanpå' noun            -> PutOn
                * multiexcept 'uppe' 'på' noun              -> PutOn
                * 'ner'/'ned' multiheld                     -> Drop
                * 'ner'/'ned'/'upp' multiexcept 'på'/'ovanpå' noun
                                                            -> PutOn
                * 'ner'/'ned'/'upp' multiexcept 'uppe' 'på' noun
                                                            -> PutOn
                * 'ner'/'ned'/'in' multiexcept 'i//'/'inuti' noun
                                                            -> Insert
                * 'ner'/'ned'/'in' multiexcept 'inne' 'i//' noun
                                                            -> Insert
                * multiexcept 'i//'/'inuti' noun            -> Insert
                * multiexcept 'inne' 'i//' noun             -> Insert
                * 'på' switchable                           -> SwitchOn
                * 'på' clothing                             -> Wear
                * 'på' creature                             -> Kiss
                * noun                                      -> Set
                * noun 'till'/'på' special                  -> SetTo;
Verb 'sök'                                                  
                * 'igenom'/'i//' noun                       -> Search;
Verb 'ta' 'plocka' 'tag'
                * multi                                     -> Take
                * 'tag' 'i//' multi                         -> Take
                * 'upp'/'fram' multi                        -> Take
                * 'av' 'mig'/'dig' noun                     -> Disrobe ! ¤#¤ This causes trouble because "mig" also refers to player
                * 'av' worn                                 -> Disrobe
                * multiinside 'från'/'ur'/'i//' noun        -> Remove
                * 'upp'/'fram'/'ut'/'ur'/'bort' multiinside 'i//'/'från'/'ur' noun
                                                            -> Remove
                * 'på' 'mig'/'dig' noun                     -> Wear ! ¤#¤ This causes trouble because "mig" also refers to player
                * 'på' clothing                             -> Wear
                * 'på' noun                                 -> Touch;
Verb 'tappa'                                     
                * noun                                      -> Drop
                * 'av'/'ur'/'ut' noun                       -> Empty
                * 'av'/'ur'/'ut' noun 'i//'/'inuti'/'ovanpå'/'på' noun
                                                            -> EmptyT;
Verb 'titta' 'se' 't//'                                     
                *                                           -> Look
                * noun=ADirection                           -> Examine
                * 'åt'/'mot' noun=ADirection                -> Examine
                * 'på' noun                                 -> Examine
                * 'närmare' 'på' noun                       -> Examine
                * 'i//'/'inuti'/'genom'/'igenom' noun       -> Search
                * 'in'/'inne' 'i//' noun                    -> Search
                * 'under' noun                              -> LookUnder;
Verb 'tryck' 'knuffa' 'putta'                               
                * noun                                      -> Push
                * 'på'/'till' noun                          -> Push
                * noun noun                                 -> PushDir
                * noun 'till' noun                          -> Transfer;
Verb 'tänk'                                                 
                *                                           -> Think;
Verb 'töm'                                       
                * noun                                      -> Empty
                * 'ut'/'ur' noun                            -> Empty
                * 'ut'/'ur' noun 'i//'/'inuti'/'på'/'ovanpå' noun
                                                            -> EmptyT;
Verb 'undersök' 'x//'                                       
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
                * 'upp' held 'för' creature                 -> Show
                * held 'för' creature                       -> Show;
Verb 'väck'                                                 
                * creature                                  -> WakeOther
                * 'upp' creature                            -> WakeOther;
Verb 'vänd' 'rotera'                                        
                * noun                                      -> Turn
                * 'runt'/'på' noun                          -> Turn;
Verb 'vänta' 'z//'                                          
                *                                           -> Wait;
Verb 'ät'                                                   
                * 'upp' held                                -> Eat
                * held                                      -> Eat;
Verb 'öppna'                                                
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
