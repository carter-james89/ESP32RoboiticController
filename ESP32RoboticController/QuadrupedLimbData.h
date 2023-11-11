#ifndef QUADRUPEDLIMBDATA_H
#define QUADRUPEDLIMBDATA_H

class QuadrupedLimbData {
public:
    float FLBaseAngle;
    float FLHipAngle;
    float FLKneeAngle;

    float FRBaseAngle;
    float FRHipAngle;
    float FRKneeAngle;

    float BRBaseAngle;
    float BRHipAngle;
    float BRKneeAngle;

    float BLBaseAngle;
    float BLHipAngle;
    float BLKneeAngle;

    // Constructor
    QuadrupedLimbData(float flBaseAngle, float flHipAngle, float flKneeAngle,
                      float frBaseAngle, float frHipAngle, float frKneeAngle,
                      float brBaseAngle, float brHipAngle, float brKneeAngle,
                      float blBaseAngle, float blHipAngle, float blKneeAngle) :
                      FLBaseAngle(flBaseAngle), FLHipAngle(flHipAngle), FLKneeAngle(flKneeAngle),
                      FRBaseAngle(frBaseAngle), FRHipAngle(frHipAngle), FRKneeAngle(frKneeAngle),
                      BRBaseAngle(brBaseAngle), BRHipAngle(brHipAngle), BRKneeAngle(brKneeAngle),
                      BLBaseAngle(blBaseAngle), BLHipAngle(blHipAngle), BLKneeAngle(blKneeAngle) {}
};

#endif // QUADRUPEDLIMBDATA_H
