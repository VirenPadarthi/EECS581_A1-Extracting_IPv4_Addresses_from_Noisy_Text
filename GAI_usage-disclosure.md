# Generative AI Usage Disclosure

## General Disclosure

**Generative AI Tool Used:** ChatGPT  5.6
I used "ChatGPT" as a gen.AI assistant while developing and reviewing this
assignment.

The AI was used to help with the initial design of the parsing logic, manual
numeric conversion, IPv4 and port validation, candidate scanning, conversion of
the four octets into a 32-bit numeric address, and organization of the main
input/output loop.

The source code marks the main AI-assisted areas using comments labeled
`(AI-Assisted)`.


# Prompts Used

The following prompts were used during development and review of the program.

## Prompt 1 — Parsing Strategy

> Write a C solution for an IPv4 extraction assignment. The program must scan
> noisy text character by character and locate candidate tokens containing only
> digits, periods, and colons. Do not use regular expressions, atoi, strtol,
> sscanf, scanf numeric conversions, or networking address-parsing functions.
> Explain how to separate garbage text from a complete candidate without
> accepting only a valid substring from a malformed token.

This prompt was used to help develop the general scanning and candidate
extraction strategy.


## Prompt 2 — Manual Numeric Parsing

> Help me design a C helper function that manually converts a sequence of digit
> characters into an integer without using any built-in string-to-number
> conversion function. The function should also reject an empty number, reject
> too many digits, reject leading zeros except for the single value 0, and
> reject values above a maximum value passed to the function.

This prompt was used to help develop the logic implemented in `parseNumber()`.


## Prompt 3 — IPv4 and Port Validation

> Help me design the validation logic for one complete IPv4 candidate in C.
> The address must contain exactly four octets separated by periods. Each octet
> must contain 1 to 3 digits, have a value from 0 to 255, and cannot contain a
> leading zero unless it is exactly 0. An optional port may appear after the
> fourth octet using a colon. The port must contain 1 to 5 digits, have a value
> from 0 to 65535, and follow the same leading-zero rule. The entire candidate
> must be rejected if extra periods, extra colons, missing fields, or other
> malformed structure remains.

This prompt was used to help structure `validateCandidate()`.


## Prompt 4 — 32-bit IPv4 Value

> Explain how to combine four validated IPv4 octets into the required 32-bit
> unsigned numeric value in C. Show both the positional interpretation
> A*256^3 + B*256^2 + C*256 + D and an equivalent implementation using bit
> shifting.

This prompt was used to help understand and verify the address construction
logic.


## Prompt 5 — Complete Candidate Scanning

> Review this C parsing approach for the full-candidate requirement. A continuous
> sequence made only of digits, periods, and colons must be treated as one
> candidate. For example, 192.168.1.1. must be rejected as a complete malformed
> candidate instead of accepting 192.168.1.1. The parser should also continue
> searching after an invalid candidate in case a later valid candidate appears.
> Identify any logical mistakes in this approach.

This prompt was used to review the logic in `extractIPv4()`.


## Prompt 6 — Main Program and Output

> Help me organize the C main function so that it repeatedly reads a complete
> line using fgets, stops only when the exact case-sensitive input END is
> entered, calls extractIPv4(), and prints the required output format. On success
> it should display the dotted IPv4 address, its decimal value, and either the
> port number or the literal text none. On failure it should print the required
> invalid-input message.

This prompt was used to help organize the main input/output loop.


## Prompt 7 — Final Review

> Review my completed C implementation against these requirements: exact
> extractIPv4 prototype, manual digit accumulation, four octets, 0-255 range,
> no invalid leading zeros, optional port from 0-65535, full-candidate
> validation, continued scanning after invalid candidates, case-sensitive END,
> and exact required output formatting. Do not rewrite the whole program.
> Identify any violations, edge cases, or output-format differences I should
> correct before submission.

This prompt was used as a final verification step.


# Code Attribution

## AI-Assisted — Candidate Character Helpers

### function

- `isDigitChar()`
- `isCandidateChar()`

- a digit
- a period `.`
- a colon `:`

I reviewed these functions and understand how they are being used by the rest of the
program.

# AI-Assisted — Manual Number Parsing

### function

- `parseNumber()`
 function rejects:

- empty numeric fields
- values containing too many digits
- leading zeros in multi-digit values
- numeric values above a supplied maximum

Numeric values are accumulated manually using:

`*value = (*value * 10) + (str[i] - '0');`

# AI-Assisted — IPv4 and Port Validation

### function

- `validateCandidate()`

- exactly four octets are present
- the first three octets are followed by periods
- every octet contains 1 to 3 digits
- every octet is between 0 and 255
- multi-digit octets cannot begin with zero
- a port is optional
- a port may appear only after the fourth octet
- the port contains 1 to 5 digits
- the port is between 0 and 65535
- a multi-digit port cannot begin with zero
- no extra candidate characters remain after parsing

I reviewed the logic against the assignment grammar and understand why each
validation check is necessary.


# AI-Assisted — 32-bit Address Construction

### function
`validateCandidate()`:

```c
*address =
    ((unsigned long)octets[0] << 24) |
    ((unsigned long)octets[1] << 16) |
    ((unsigned long)octets[2] << 8) |
    (unsigned long)octets[3];