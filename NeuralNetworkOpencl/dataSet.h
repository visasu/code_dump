
#define trainSamples 60000
#define testSamples 10000
#define OutputLength 10
#define ROW 28
#define COL 28
#define Layer_1_Size ROW*COL
#define Layer_2_Size 28
#define Theta1SIZE (Layer_2_Size-1)*Layer_1_Size
#define Theta2SIZE OutputLength*Layer_2_Size
#define XSIZE trainSamples*Layer_1_Size
#define YSIZE trainSamples*OutputLength
#define XpSIZE testSamples*Layer_1_Size
#define YpSIZE testSamples*OutputLength
#define L1KerDimX 196
#define L1KerDimY 240
#define L1KerDimZ 250

#define L2KerDimX 7
#define L2KerDimY 240
#define L2KerDimZ 250

extern float X[trainSamples][Layer_1_Size];
extern float Y[trainSamples][OutputLength];
extern float Xp[testSamples][Layer_1_Size];
extern float Yp[testSamples][OutputLength];
extern float Theta1[Layer_2_Size-1][Layer_1_Size];
extern float Theta2[OutputLength][Layer_2_Size];
