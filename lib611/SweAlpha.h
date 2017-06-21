! Contains a Z-machine alphabet optimised for Swedish. Must be included 
! before any text in encoded, even before declaring the constants Story and 
! Headline.
!
! It is not absolutely necessary to include this file, but without it, 
! dictionary words containing "åäö" may be reduced to the 2-6 first 
! characters, rather than 9. This file is only relevant for Zcode games,
! not Glulx.
!
! If you don't agree with this Zcharacter directive, make your own instead. 
! Just make sure that åäö is included in the table, and that line 2 is an 
! upper case version of line 1.

#ifdef TARGET_ZCODE;
Zcharacter "abcdefghijklmnoprstuvxyåäö"
           "ABCDEFGHIJKLMNOPRSTUVXYÅÄÖ"
              "012345.,!?'/-:()wqzWQZé";
#endif;

