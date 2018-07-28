use Test::More qw(no_plan);
use IPC::Open2;

if (/^\s*{\s*input:\s*"(.+)",\s*output:\s*"(.+)"/) {
    my $pid = open2(\*CHLD_OUT, \*CHLD_IN, "build/amath");
    print CHLD_IN $1;
    close(CHLD_IN);
    is(<CHLD_OUT>, $2 . "\n");
    close(CHLD_OUT);
}
