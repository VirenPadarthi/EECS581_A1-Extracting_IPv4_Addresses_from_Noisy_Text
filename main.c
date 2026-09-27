// Name : Viren Padarthi
// KU ID : 3131950
// A1 : Extracting IPv4 Addresses from Noisy Text
// Date : 9/24
// Date last modified : 9/27
// Sources : Chat GPT, Stack Overflow, geeksforgeeks, Grammarly

#include <stdio.h>
#include <string.h>

#define MAX_INPUT 1000


/*
 * (AI-Assisted) — Candidate Character Helpers
 *
 * I used GAI (chatgpt) to help me organize the character-level checks used
 * by the parser. These helper functions helped me differ decmial digits from
 * the characters that are allowed to appear inside an IPv4 candidate.
 * 
 * Prompt used:
 * I asked GAI to help me with a function that checks if a character is a digit
 * and another function that checks if a character is a candidate character (digit, period, or teh colon).
 * ""
 *
 * I reviewed this block and understand how these helper functions are used by rest of the parser.
 */


/* Returns 1 if c is a digit, 0 otherwise. */
int isDigitChar(char c)
{
    return c >= '0' && c <= '9';
}

/* Candidate characters are digits, periods, and colons. */
int isCandidateChar(char c)
{
    return isDigitChar(c) || c == '.' || c == ':';
}


/*
 * (AI-Assisted) — Manual Number Parsing
 *
 * AI assistance was used for the initial structure of the manual numeric
 * parsing logic. This section converts digit characters into integer values
 * without using prohibited conversion functions such as atoi, strtol,
 * sscanf, or scanf numeric conversions.
 *
 * AI assistance also helped identify the checks needed for:
 * - empty numeric fields
 * - maximum number of digits
 * - leading zeros
 * - maximum allowed numeric value
 *
 * Prompt used:
 * I provided the complete assignment specification to ChatGPT and asked:
 * "aight help me pls pls lps"
 *
 * I reviewed this block and understand that the numeric value is built
 * manually using:
 *
 * value = value * 10 + (digit - '0')
 */


/*
 * Manually converts characters from str[start] through str[end - 1]
 * into an integer.
 *
 * Returns 1 when valid and 0 when invalid.
 */
int parseNumber(const char *str,
                int start,
                int end,
                int maxDigits,
                int maxValue,
                int *value)
{
    int length;
    int i;

    if (start >= end)
        return 0;

    length = end - start;

    if (length > maxDigits)
        return 0;

    /* Leading zero is allowed only when the number is exactly "0". */
    if (length > 1 && str[start] == '0')
        return 0;

    *value = 0;

    for (i = start; i < end; i++)
    {
        if (!isDigitChar(str[i]))
            return 0;

        /*
         * Manual digit accumulation.
         *
         * Example: "25"
         * 0 * 10 + 2 = 2
         * 2 * 10 + 5 = 25
         */
        *value = (*value * 10) + (str[i] - '0');

        if (*value > maxValue)
            return 0;
    }

    return 1;
}


/*
 * (AI-Assisted) — IPv4 and Port Validation
 *
 * AI assistance was used to help structure the complete validation of an
 * IPv4 candidate. This section parses exactly four octets and validates
 * the optional port number.
 *
 * The logic checks:
 * - exactly four octets
 * - required periods between octets
 * - octet values from 0 through 255
 * - one to three digits per octet
 * - leading-zero restrictions
 * - an optional colon and port
 * - port values from 0 through 65535
 * - one to five digits for a port
 * - rejection of malformed remaining characters
 *
 * Prompts used:
 *
 * I provided the complete assignment specification to ChatGPT and asked:
 * "aight help me pls pls lps"
 *
 * I later requested that the program use C:
 * "why not in c? alo dont be like eerhing i s generated in AI im adumb idiot okay? commmon"
 *
 * I reviewed this section against the grammar given in the assignment.
 */


/*
 * Validates one entire candidate from start through end - 1.
 *
 * Valid forms:
 *
 * A.B.C.D
 *
 * or
 *
 * A.B.C.D:PORT
 */
int validateCandidate(const char *str,
                      int start,
                      int end,
                      unsigned long *address,
                      int *port)
{
    int octets[4] = {0, 0, 0, 0};
    int position = start;
    int octetIndex;

    for (octetIndex = 0; octetIndex < 4; octetIndex++)
    {
        int numberStart = position;

        /* Read the digits belonging to this octet. */
        while (position < end && isDigitChar(str[position]))
        {
            position++;
        }

        if (!parseNumber(str,
                         numberStart,
                         position,
                         3,
                         255,
                         &octets[octetIndex]))
        {
            return 0;
        }

        /*
         * The first three octets must be followed
         * immediately by a period.
         */
        if (octetIndex < 3)
        {
            if (position >= end || str[position] != '.')
                return 0;

            position++;
        }
    }

    *port = -1;

    /*
     * If anything remains after the fourth octet,
     * it must be exactly one colon followed by a valid port.
     */
    if (position < end)
    {
        int portStart;

        if (str[position] != ':')
            return 0;

        position++;
        portStart = position;

        while (position < end && isDigitChar(str[position]))
        {
            position++;
        }

        if (!parseNumber(str,
                         portStart,
                         position,
                         5,
                         65535,
                         port))
        {
            return 0;
        }
    }

    /*
     * Anything still remaining means the complete candidate
     * does not match the required grammar.
     */
    if (position != end)
        return 0;


    /*
     * (AI-Assisted) — 32-bit adress construction
     *
     * AI assistance was used to help explain and construct the conversion
     * from four IPv4 octets into the required 32-bit numeric address.
     *
     * Prompt used:
     * "do the full thing fully"
     *
     * I reviewed this operation and understand that:
     * - the first octet is shifted left 24 bits
     * - the second octet is shifted left 16 bits
     * - the third octet is shifted left 8 bits
     * - the fourth octet remains in the lowest byte
     */

    *address =
        ((unsigned long)octets[0] << 24) |
        ((unsigned long)octets[1] << 16) |
        ((unsigned long)octets[2] << 8) |
        (unsigned long)octets[3];

    return 1;
}


/*
 * (AI-Assisted) — Candidate Extraction and Scanning
 *
 * AI assistance was used to help develop the scanning strategy used by
 * extractIPv4().
 *
 * The function skips unrelated garbage characters and then collects an
 * entire continuous candidate consisting only of digits, periods, and
 * colons before attempting to validate it.
 *
 * This is important because a malformed candidate such as:
 *
 * 192.168.1.1.
 *
 * must be rejected in full instead of incorrectly accepting only:
 *
 * 192.168.1.1
 *
 * The function also continues scanning after an invalid candidate so that
 * a later valid candidate can still be found.
 *
 * Prompts used:
 *
 * I provided the complete assignment specification to ChatGPT and asked:
 * "aight help me pls pls lps"
 *
 * I later requested the C implementation with:
 * "why not in c? alo dont be like eerhing i s generated in AI im adumb idiot okay? commmon"
 *
 * I reviewed this scanning behavior against the assignment requirements.
 */


/*
 * Returns 1 if a valid address was found, 0 otherwise.
 *
 * On success:
 *     *outAddress contains the 32-bit IPv4 value
 *     *outPort contains the port or -1 if no port exists
 *
 * On failure:
 *     *outAddress = 0
 *     *outPort = -1
 */
int extractIPv4(const char *str,
                unsigned long *outAddress,
                int *outPort)
{
    int i = 0;
    int length = (int)strlen(str);

    *outAddress = 0;
    *outPort = -1;

    while (i < length)
    {
        int start;
        unsigned long candidateAddress;
        int candidatePort;

        /*
         * Skip garbage until a digit, period,
         * or colon begins a possible candidate.
         */
        while (i < length && !isCandidateChar(str[i]))
        {
            i++;
        }

        if (i >= length)
            break;

        start = i;

        /*
         * Capture the ENTIRE continuous candidate.
         *
         * For example:
         *
         * 192.168.1.1.
         *
         * must be treated as one candidate and rejected rather than
         * accepting only 192.168.1.1.
         */
        while (i < length && isCandidateChar(str[i]))
        {
            i++;
        }

        candidateAddress = 0;
        candidatePort = -1;

        if (validateCandidate(str,
                              start,
                              i,
                              &candidateAddress,
                              &candidatePort))
        {
            *outAddress = candidateAddress;
            *outPort = candidatePort;
            return 1;
        }
    }

    return 0;
}


/*
 * (AI-Assisted) — Main input/output loop
 *
 * AI assistance was used to help organize the continuous input loop and
 * connect the required extractIPv4() function to the required output.
 *
 * This section handels:
 * - repeatedly reading an input line
 * - recognizing the exact input END
 * - calling extractIPv4()
 * - recovering the four octets from the stored address value
 * - displaying the address, decimal value, and optional port
 *
 * Prompt used:
 * "do the full thing fully"
 *
 * I reviewed this control flow and understand how main() communicates with
 * extractIPv4() through outAddress and outPort.
 */


int main(void)
{
    char input[MAX_INPUT];

    while (1)
    {
        unsigned long address;
        int port;

        printf("Enter a string (or 'END' to quit): ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        /* Remove newline added by fgets(). */
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "END") == 0)
        {
            printf("Program terminated.\n");
            break;
        }

        address = 0;
        port = -1;

        if (extractIPv4(input, &address, &port))
        {
            unsigned long a = (address >> 24) & 255UL;
            unsigned long b = (address >> 16) & 255UL;
            unsigned long c = (address >> 8) & 255UL;
            unsigned long d = address & 255UL;

            printf(
                "Extracted IPv4 address: %lu.%lu.%lu.%lu "
                "(decimal value: %lu, port: ",
                a,
                b,
                c,
                d,
                address
            );

            if (port == -1)
            {
                printf("none");
            }
            else
            {
                printf("%d", port);
            }

            printf(")\n");
        }
        else
        {
            printf("Invalid input: no valid IPv4 address found\n");
        }
    }

    return 0;
}