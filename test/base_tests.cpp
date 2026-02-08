#include <cassert>
#include <string>
#include <iostream>
using namespace std;

// =====  project functions  =====

bool validateDNA(string dna);
string extractSTR(string dna, string LF, string RF);
int countRepeats(string str, string motif);
double smithWaterman(string s1, string s2);
string detectRelationship(double sim);

// ==========================================================

namespace D3S1358Tests {

    const string LF = "TGGGCTGAGGCTGAGTGC";
    const string RF = "CCTATGACCATGTAGACC";
    const string MOTIF = "AGAT";

    // ---------------- DNA VALIDATION ----------------
    void DNAValidation() {
        assert(validateDNA("ATGCAGATAGAT") == true);
        assert(validateDNA("ATGC12@#") == false);
        assert(validateDNA("") == false);
    }

    // ---------------- FLANK & STR EXTRACTION ----------------
    void FlankExtraction() {
        string dna1 = LF + "AGATAGATAGAT" + RF;
        assert(extractSTR(dna1, LF, RF) == "AGATAGATAGAT");

        string dna2 = LF + "AGATAGATAGAT";
        assert(extractSTR(dna2, LF, RF).empty());

        string dna3 = "AGATAGAT" + RF;
        assert(extractSTR(dna3, LF, RF).empty());

        string dna4 = RF + LF + "AGATAGAT" + RF;
        assert(extractSTR(dna4, LF, RF) == "AGATAGAT");
    }

    // ---------------- STR PATTERNS ----------------
    void STRPatterns() {
        string dna5 = LF + "AGATAGATAGATAGAT" + RF;
        assert(extractSTR(dna5, LF, RF) == "AGATAGATAGATAGAT");

        string dna6 = LF + "AGATAGTTAGAT" + RF;
        assert(extractSTR(dna6, LF, RF) == "AGATAGTTAGAT");

        string dna7 = LF + RF;
        assert(extractSTR(dna7, LF, RF).empty());
    }

    // ---------------- MULTIPLE LOCI ----------------
    void MultipleLoci() {
        string dnaA = LF + "AGATAGATAGAT" + RF;
        string dnaB = LF + "AGATAGATAGATAGAT" + RF;
        string dna = dnaA + "ATCGATCG" + dnaB;

        assert(extractSTR(dna, LF, RF) == "AGATAGATAGAT");
    }

    // ---------------- REPEAT COUNTING ----------------
    void RepeatCounting() {
        assert(countRepeats("AGATAGATAGAT", MOTIF) == 3);
        assert(countRepeats("AGATAGTTAGAT", MOTIF) == 1);

        string longSTR;
        for(int i = 0; i < 50; i++)
            longSTR += MOTIF;

        assert(countRepeats(longSTR, MOTIF) == 50);
    }

    // ---------------- SMITH WATERMAN ----------------
    void SmithWatermanTests() {
        assert(smithWaterman("AGATAGAT", "AGATAGAT") == 100.0);
        assert(smithWaterman("AGATAGAT", "AGATAGATAGAT") > 70.0);
        assert(smithWaterman("AGATAGAT", "AGTTAGAT") < 90.0);
        assert(smithWaterman("AGATAGAT", "TTTTCCCC") < 30.0);
    }

    // ---------------- RELATIONSHIP DETECTION ----------------
    void RelationshipDetection() {
        assert(detectRelationship(100.0) == "Same Person");
        assert(detectRelationship(75.0) == "Father-Son");
        assert(detectRelationship(55.0) == "Siblings");
        assert(detectRelationship(20.0) == "Unrelated");
    }

    // ---------------- REAL LOCUS SCENARIO ----------------
    void RealLocusScenario() {
        string realDNA = LF + "AGATAGATAGATAGATAGAT" + RF;
        string str = extractSTR(realDNA, LF, RF);

        assert(!str.empty());
        assert(smithWaterman(str, "AGATAGATAGATAGAT") > 70.0);
        assert(smithWaterman(str, "TTTTCCCC") < 30.0);
    }

    // ---------------- BOUNDARY CASES ----------------
    void BoundaryCases() {
        string realDNA = LF + "AGATAGATAGATAGAT" + RF;

        assert(extractSTR("", LF, RF).empty());
        assert(extractSTR(realDNA, "", "").empty());
        assert(extractSTR("AGAT", LF, RF).empty());
    }

} // namespace D3S1358Tests


// ---------------- TEST RUNNER ----------------
int main() {
    using namespace D3S1358Tests;

    DNAValidation();
    FlankExtraction();
    STRPatterns();
    MultipleLoci();
    RepeatCounting();
    SmithWatermanTests();
    RelationshipDetection();
    RealLocusScenario();
    BoundaryCases();

    cout << "All D3S1358 unit tests passed successfully.\n";
    return 0;
}

