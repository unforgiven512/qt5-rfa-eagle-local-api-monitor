#ifndef RFADEFAULTCREDS_H_
#define RFADEFAULTCREDS_H_



#if defined(USE_RFA_DEFAULT_CREDS)

#if (!defined(RFA_DEFAULT_CREDS_USER) || !defined(RFA_DEFAULT_CREDS_PASS))
#warning 'Using the hard-coded default credentials from rfa-default-creds.h file'

#define RFA_CREDS_USER "0076f6"
#define RFA_CREDS_PASS "37e24fe9a9017f49"
//http=0076f6:37e24fe9a9017f49

#elif (defined(RFA_DEFAULT_CREDS_USER) && defined(RFA_DEFAULT_CREDS_PASS))

#define RFA_CREDS_USER RFA_DEFAULT_CREDS_USER
#define RFA_CREDS_PASS RFA_DEFAULT_CREDS_PASS

#else

#error 'Both "RFA_DEFAULT_CREDS_USER" and "RFA_DEFAULT_CREDS_PASS" must be defined!'

#endif

#endif



#endif	/* !RFADEFAULTCREDS_H_ */
