#include <iostream>
#include <vector>
#include <iomanip>
// DBoW2
#include "DBoW2.h" // defines OrbVocabulary and OrbDatabase

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

using namespace DBoW2;
using namespace std;

const int NIMAGES = 2000;

void loadFeatures(vector<vector<cv::Mat>> &features);
void changeStructure(const cv::Mat &plain, vector<cv::Mat> &out);
void testVocCreation(const vector<vector<cv::Mat>> &features, vector<pair<int, int>> &detected);

void loadFeatures(vector<vector<cv::Mat>> &features)
{
  features.clear();
  features.reserve(NIMAGES);

  cv::Ptr<cv::ORB> orb = cv::ORB::create(1500);

  cout << "Extracting ORB features..." << endl;
  for (int i = 0; i < NIMAGES; ++i)
  {
    stringstream ss;
    ss << "/home/leejaewon/RAIL/dataset/sequences/00/image_0/" << std::setw(6) << std::setfill('0') << i << ".png";

    cv::Mat image = cv::imread(ss.str(), 0);
    cv::Mat mask;
    vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;

    orb->detectAndCompute(image, mask, keypoints, descriptors);
    cv::drawKeypoints(image, keypoints, image, cv::Scalar(0, 255, 0));

    cv::imshow("img_DBoW2_previous", image);

    features.push_back(vector<cv::Mat>());
    changeStructure(descriptors, features.back());

    cv::waitKey(1);
  }
  cv::destroyWindow("img_DBoW2_previous");
}

void changeStructure(const cv::Mat &plain, vector<cv::Mat> &out)
{
  out.resize(plain.rows);

  for (int i = 0; i < plain.rows; ++i)
  {
    out[i] = plain.row(i);
  }
}

void testVocCreation(const vector<vector<cv::Mat>> &features, vector<pair<int, int>> &detected)
{
  // branching factor and depth levels
  const int k = 9;
  const int L = 3;
  const WeightingType weight = TF_IDF;
  const ScoringType scoring = L1_NORM;

  OrbVocabulary voc(k, L, weight, scoring);

  cout << "Creating a small " << k << "^" << L << " vocabulary..." << endl;
  voc.create(features);
  cout << "... done!" << endl;

  cout << "Vocabulary information: " << endl
       << voc << endl
       << endl;

  // lets do something with this vocabulary
  cout << "Matching images against themselves (0 low, 1 high): " << endl;
  BowVector v1, v2;
  for (int i = 0; i < NIMAGES; i++)
  {
    stringstream ss;
    ss << "/home/leejaewon/RAIL/dataset/sequences/00/image_0/" << std::setw(6) << std::setfill('0') << i << ".png";
    cv::Mat image = cv::imread(ss.str(), 0);
    cv::imshow("img_loop_evaluate", image);

    voc.transform(features[i], v1);
    for (int j = 0; j < i; j++)
    {
      voc.transform(features[j], v2);

      double score = voc.score(v1, v2);

      if (score >= 0.7 && (i - j) > 10)
      {
        cout << "Image " << i << " vs Image " << j << ": " << score << endl;
        detected.push_back(make_pair(i, j));
      }
    }
    cv::waitKey(1);
  }
  cv::destroyWindow("img_loop_evaluate");

  // save the vocabulary to disk
  cout << endl
       << "Saving vocabulary..." << endl;
  voc.save("small_voc.yml.gz");
  cout << "Done" << endl;
}