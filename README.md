# EECS581_A1-Extracting_IPv4_Addresses_from_Noisy_Text

# A1: Extracting IPv4 Addresses from Noisy Text

This project implements a C program that extracts a valid IPv4 address,
optionally followed by a port number, from noisy input text.

## IPv4 Format

A valid address has the form:

`A.B.C.D`

A port may optionally follow:

`A.B.C.D:PORT`

Each IPv4 octet:

- Contains between 1 and 3 digits
- Has a numeric value between 0 and 255
- Cannot contain leading zeros unless the value is exactly `0`

The optional port:

- Contains between 1 and 5 digits
- Has a numeric value between 0 and 65535
- Cannot contain leading zeros unless its value is exactly `0`

## Parsing Behavior

The program scans through noisy text looking for candidate tokens.

Only the following characters may be part of a candidate:

- Digits
- Period `.`
- Colon `:`

All other characters are treated as garbage separating candidates.

Candidates are validated in full.

For example:

`192.168.1.1.`

is rejected rather than being shortened to:

`192.168.1.1`

The program also continues searching after an invalid candidate.

For example:

`999.999.999.999 text 10.20.30.40`

allows the first malformed candidate to be rejected and the later valid
address to be extracted.

## Manual Numeric Conversion

The assignment prohibits functions such as:

- `atoi`
- `atol`
- `strtol`
- `strtoul`
- `sscanf`
- `scanf` numeric conversions

The implementation instead converts characters manually using:

`value = value * 10 + (digit - '0')`

## Other Restrictions

The implementation does not use:

- Regular expressions
- `inet_aton`
- `inet_pton`
- `inet_addr`
- Other IPv4 parsing libraries

## Required Function

The program implements:

```c
int extractIPv4(
    const char* str,
    unsigned long* outAddress,
    int* outPort
);
