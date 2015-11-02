/*
 * Copyright (c) 2012,2015 Apple Inc. All rights reserved.
 * 
 * corecrypto Internal Use License Agreement
 * 
 * IMPORTANT:  This Apple corecrypto software is supplied to you by Apple Inc. ("Apple")
 * in consideration of your agreement to the following terms, and your download or use
 * of this Apple software constitutes acceptance of these terms.  If you do not agree
 * with these terms, please do not download or use this Apple software.
 * 
 * 1.	As used in this Agreement, the term "Apple Software" collectively means and
 * includes all of the Apple corecrypto materials provided by Apple here, including
 * but not limited to the Apple corecrypto software, frameworks, libraries, documentation
 * and other Apple-created materials. In consideration of your agreement to abide by the
 * following terms, conditioned upon your compliance with these terms and subject to
 * these terms, Apple grants you, for a period of ninety (90) days from the date you
 * download the Apple Software, a limited, non-exclusive, non-sublicensable license
 * under Apple’s copyrights in the Apple Software to make a reasonable number of copies
 * of, compile, and run the Apple Software internally within your organization only on
 * devices and computers you own or control, for the sole purpose of verifying the
 * security characteristics and correct functioning of the Apple Software; provided
 * that you must retain this notice and the following text and disclaimers in all
 * copies of the Apple Software that you make. You may not, directly or indirectly,
 * redistribute the Apple Software or any portions thereof. The Apple Software is only
 * licensed and intended for use as expressly stated above and may not be used for other
 * purposes or in other contexts without Apple's prior written permission.  Except as
 * expressly stated in this notice, no other rights or licenses, express or implied, are
 * granted by Apple herein.
 * 
 * 2.	The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES
 * OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING
 * THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS,
 * SYSTEMS, OR SERVICES. APPLE DOES NOT WARRANT THAT THE APPLE SOFTWARE WILL MEET YOUR
 * REQUIREMENTS, THAT THE OPERATION OF THE APPLE SOFTWARE WILL BE UNINTERRUPTED OR
 * ERROR-FREE, THAT DEFECTS IN THE APPLE SOFTWARE WILL BE CORRECTED, OR THAT THE APPLE
 * SOFTWARE WILL BE COMPATIBLE WITH FUTURE APPLE PRODUCTS, SOFTWARE OR SERVICES. NO ORAL
 * OR WRITTEN INFORMATION OR ADVICE GIVEN BY APPLE OR AN APPLE AUTHORIZED REPRESENTATIVE
 * WILL CREATE A WARRANTY. 
 * 
 * 3.	IN NO EVENT SHALL APPLE BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING
 * IN ANY WAY OUT OF THE USE, REPRODUCTION, COMPILATION OR OPERATION OF THE APPLE
 * SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING
 * NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * 4.	This Agreement is effective until terminated. Your rights under this Agreement will
 * terminate automatically without notice from Apple if you fail to comply with any term(s)
 * of this Agreement.  Upon termination, you agree to cease all use of the Apple Software
 * and destroy all copies, full or partial, of the Apple Software. This Agreement will be
 * governed and construed in accordance with the laws of the State of California, without
 * regard to its choice of law rules.
 * 
 * You may report security issues about Apple products to product-security@apple.com,
 * as described here:  https://www.apple.com/support/security/.  Non-security bugs and
 * enhancement requests can be made via https://bugreport.apple.com as described
 * here: https://developer.apple.com/bug-reporting/
 *
 * EA1350 
 * 10/5/15
 */

#define USE_SUPER_COOL_NEW_CCOID_T
#include "testmore.h"
#include "testbyteBuffer.h"

static int verbose = 0;

#if (CCWRAPTEST == 0)
entryPoint(ccwraptest,"ccwrap test")
#else
#include <corecrypto/ccmode.h>
#include <corecrypto/ccaes.h>
#include <corecrypto/ccwrap.h>

#define KEY128 "000102030405060708090a0b0c0d0e0f"
#define KEY192 "000102030405060708090a0b0c0d0e0f0001020304050607"
#define KEY256 "000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f"
#define KEY512 "000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f"

static int test_wrap(const struct ccmode_ecb *enc_ecb, const struct ccmode_ecb *dec_ecb, char *keydata, char *kekdata) {
    ccecb_ctx_decl(enc_ecb->size, enc_ctx);
    ccecb_ctx_decl(dec_ecb->size, dec_ctx);
    byteBuffer kek = hexStringToBytes(kekdata);

    ccecb_init(enc_ecb, enc_ctx, kek->len, kek->bytes);
    ccecb_init(dec_ecb, dec_ctx, kek->len, kek->bytes);
    
    byteBuffer key = hexStringToBytes(keydata);
    size_t wrapped_size =  ccwrap_wrapped_size(key->len);
    byteBuffer wrapped_key = mallocByteBuffer(wrapped_size);

    
    ok(ccwrap_auth_encrypt(enc_ecb, enc_ctx,
                           key->len, key->bytes,
                           &wrapped_size, wrapped_key->bytes) == 0, "Wrapped Key");
    
    size_t unwrapped_size =  ccwrap_unwrapped_size(wrapped_size);
    byteBuffer unwrapped_key = mallocByteBuffer(unwrapped_size);

    ok(ccwrap_auth_decrypt(dec_ecb, dec_ctx,
                           wrapped_key->len, wrapped_key->bytes,
                           &unwrapped_size, unwrapped_key->bytes) == 0, "Unwrapped Key");
    ok(bytesAreEqual(key, unwrapped_key), "Round Trip Success");
    free(key);
    free(wrapped_key);
    free(unwrapped_key);
    return 1;
}

int ccwraptest(TM_UNUSED int argc, TM_UNUSED char *const *argv)
{
	plan_tests(36);
    if(verbose) diag("Starting ccwrap tests\n");
    const struct ccmode_ecb *enc_ecb = ccaes_ecb_encrypt_mode();
    const struct ccmode_ecb *dec_ecb = ccaes_ecb_decrypt_mode();
    ok(test_wrap(enc_ecb, dec_ecb, KEY128, KEY128), "ccwrap of 128 bit key with 128 bit kek");
    ok(test_wrap(enc_ecb, dec_ecb, KEY256, KEY128), "ccwrap of 256 bit key with 128 bit kek");
    ok(test_wrap(enc_ecb, dec_ecb, KEY512, KEY128), "ccwrap of 512 bit key with 128 bit kek");
    ok(test_wrap(enc_ecb, dec_ecb, KEY128, KEY192), "ccwrap of 128 bit key with 192 bit kek");
    ok(test_wrap(enc_ecb, dec_ecb, KEY256, KEY192), "ccwrap of 256 bit key with 192 bit kek");
    ok(test_wrap(enc_ecb, dec_ecb, KEY512, KEY192), "ccwrap of 512 bit key with 192 bit kek");
    ok(test_wrap(enc_ecb, dec_ecb, KEY128, KEY256), "ccwrap of 128 bit key with 256 bit kek");
    ok(test_wrap(enc_ecb, dec_ecb, KEY256, KEY256), "ccwrap of 256 bit key with 256 bit kek");
    ok(test_wrap(enc_ecb, dec_ecb, KEY512, KEY256), "ccwrap of 512 bit key with 256 bit kek");
    return 0;
}
#endif

