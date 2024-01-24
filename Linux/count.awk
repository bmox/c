#write a AWK script to find the number of characters,
#words and lines in a text file.
#!/usr/bin/awk -f

{
    # Count characters
    char_count += length

    # Count words
    word_count += NF

    # Count lines
    line_count++
}

END {
    print "Number of characters: " char_count
    print "Number of words: " word_count
    print "Number of lines: " line_count
}


#@cloudshell:~$
#cat << EOF > example.txt
#This is a sample text file.
#It has multiple lines for testing.
#Feel free to add more content.
#EOF
#@cloudshell:~$ nano run.awk
#@cloudshell:~$ chmod +x run.awk
#@cloudshell:~$ ./run.awk example.txt
#Number of characters: 91
#Number of words: 18
#Number of lines: 3