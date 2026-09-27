# Generative AI Usage Disclosure

## General Disclosure

**Generative AI Tool Used:** ChatGPT  
**Model:** GPT-5.6 Sol  
**Date Used:** September 27, 2026

I used ChatGPT as a generative AI assistant while working on this assignment.

AI assistance was used for several meaningful parts of the program, including
the character-level parsing approach, manual number conversion, IPv4 and port
validation, candidate extraction, construction of the 32-bit IPv4 value, and
organization of the main input/output loop.

The source code identifies the AI-assisted portions using the following labels:

- **AI-Assisted Block A — Candidate Character Helpers**
- **AI-Assisted Block B — Manual Number Parsing**
- **AI-Assisted Block C — IPv4 and Port Validation**
- **AI-Assisted Block D — 32-bit Address Construction**
- **AI-Assisted Block E — Candidate Extraction and Scanning**
- **AI-Assisted Block F — Main Input / Output Loop**

Basic syntax such as include statements, constants, simple declarations, braces,
and other routine C syntax were not separately identified as AI-assisted.


# Prompts Used

## Prompt 1 — Initial Assignment Help

I pasted the complete assignment specification from Canvas into ChatGPT,
including:

- The IPv4 extraction requirements
- The required C and C++ function prototypes
- The IPv4 octet rules
- The optional port rules
- The prohibited library functions
- The requirement to perform manual numeric conversion
- The continuous input loop requirement
- The required output format
- The sample run
- The testing requirements
- The AI disclosure requirements

After pasting the assignment specification, I asked:

> "aight help me pls pls lps"

This prompt began the discussion of how the assignment could be approached.


## Prompt 2 — Request to Use C

After an initial C++ solution was discussed, I requested that the assignment be
implemented in C instead.

My prompt was:

> "why not in c? alo dont be like eerhing i s generated in AI im  adumb idiot okay? commmon"

This changed the implementation direction from C++ to C.


## Prompt 3 — Complete C Version

I then asked:

> "do the full thing fully"

This prompt was used to help produce the more complete C implementation and
supporting submission structure.


## Prompt 4 — Code-Level AI Attribution

After reviewing the code, I asked for the AI-assisted parts to be identified
inside the source code.

My prompt was:

> "the code iks good i suppsoe um dont achange anyhrig even typs cuz the typos of spacing were intentional u just add the comments or document in this code parts where Ai is used; just do for the hardest parts..."

This resulted in adding code comments describing where AI assistance was used.


## Prompt 5 — Expanded AI Attribution

I then decided that the disclosure should identify AI assistance for most of
the meaningful program logic instead of only the most difficult sections.

My prompt was:

> "naaah let sod this;in the code; memtion that its AI assited, then int he documentation md file mention the ai asssted block exactly in th ecode in both i want the "prompt " used section...also not just for the hardest parts; lets do for almost all of the code except for parts that dont need ai"

This led to the final AI-Assisted Block A through Block F labeling system.


## Prompt 6 — Final Source Code Draft

I then requested the final complete source code draft:

> "im aking last time; now generate the fully final code draft ill paste"

This produced the final version of the C source code containing the matching
AI-Assisted Block A through Block F comments.


# Code Attribution

## AI-Assisted Block A — Candidate Character Helpers

### Code Involved

- `isDigitChar()`
- `isCandidateChar()`

### AI Assistance

AI assistance was used to help organize the character-level checks used by the
parser.

`isDigitChar()` determines whether a character is a decimal digit.

`isCandidateChar()` determines whether a character is allowed to be part of a
candidate token.

According to the assignment, the only characters that can belong to a valid
candidate are:

- digits
- period `.`
- colon `:`

These helper functions are then reused by the rest of the parser.

### My Review

I reviewed this block and understand that these functions do not determine
whether an IPv4 address is valid. They only help identify characters that could
belong to a candidate.


# AI-Assisted Block B — Manual Number Parsing

### Code Involved

- `parseNumber()`

### AI Assistance

AI assistance was used to help structure the manual numeric conversion logic.

Because the assignment prohibits functions such as:

- `atoi`
- `atol`
- `strtol`
- `strtoul`
- `sscanf`
- numeric `scanf` conversions

the program converts digit characters manually.

The main operation is:

`*value = (*value * 10) + (str[i] - '0');`

AI assistance also helped identify the validation checks performed in this
function:

- Reject an empty numeric field
- Reject too many digits
- Reject invalid leading zeros
- Reject values above the allowed maximum

### My Review

I understand how the manual conversion works.

For example, the text `255` is accumulated as:

- Start with 0
- `0 * 10 + 2 = 2`
- `2 * 10 + 5 = 25`
- `25 * 10 + 5 = 255`

This allows the program to convert numeric text without using prohibited
conversion functions.


# AI-Assisted Block C — IPv4 and Port Validation

### Code Involved

- `validateCandidate()`

### AI Assistance

AI assistance was used to help structure the validation of a complete IPv4
candidate.

This block checks that an IPv4 address contains exactly four octets.

For each octet, the program verifies:

- It is present
- It contains between 1 and 3 digits
- Its value is between 0 and 255
- It does not contain a leading zero unless the value is exactly `0`

The block also handles the optional port.

When a colon is present after the fourth octet, the program checks that the
port:

- Is present
- Contains between 1 and 5 digits
- Has a value between 0 and 65535
- Does not contain a leading zero unless the value is exactly `0`

The function also rejects any remaining characters that prevent the entire
candidate from matching the required grammar.

### My Review
I reviewed this block against the assignment specification. Also, i understand why the first three octets must each be followed by a period, why the fourth octet is treated differently, and why a colon is only valid after
the fourth octet s.

# AI-Assisted Block D — 32-bit Address Construction

### Code Involved

The following operation inside `validateCandidate()`:

```c
*address =
    ((unsigned long)octets[0] << 24) |
    ((unsigned long)octets[1] << 16) |
    ((unsigned long)octets[2] << 8) |
    (unsigned long)octets[3];