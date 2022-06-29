import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv)!=3:
        print("Missing command line argument")
        sys.exit(1)
    # TODO: Read database file into a variable
    db_file=sys.argv[1]
    sq_file=sys.argv[2]
    csvfile1=open(db_file, "r")
    csvfile2= open(sq_file, "r")
    reader=csv.DictReader(csvfile1)
    Sequence_database=reader.fieldnames[1:]
    #dict_list = list(reader)
    #print(dict_list)
    sequence= csvfile2.read()
    csvfile2.close()
    dna_fingerprint={}
    for sequences in Sequence_database:
        dna_fingerprint=consec_rpt(sequences,sequence)
    for row in reader:
        if match(Sequence_database,dna_fingerprint,row):
            print(f"{row['name']}")
            csvfile1.close()
            sys.exit(0)
    # TODO: Read DNA sequence file into a variable
    # TODO: Find longest match of each STR in DNA sequence
    # TODO: Check database for matching profiles
    csvfile1.close()
    sys.exit(2)

def consec_rpt(str,dna):
    i=0
    while str*(i+1) in dna:
        i+=1
    return i

def match(strs, dna_print, row):
    for str in strs:
        if dna_print[str] != int(row[str]):
            return False
    return True

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
