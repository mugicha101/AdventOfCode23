#include <bits/stdc++.h>
#include <Eigen/Dense>
#include <Eigen/Core>

using namespace std;
typedef long long ll;
typedef long double ld;

struct Segment {
    ll x, y, z, vx, vy, vz;
};

vector<Segment> readInput() {
    string line;
    vector<Segment> segs;
    while (getline(cin, line)) {
        line.push_back(',');
        int i = 0;
        auto next = [&](char delim) {
            ll val = 0;
            bool neg = false;
            while (line[i] != delim) {
                if (line[i] == '-') neg = true;
                else val = val * 10 + (line[i] - '0');
                ++i;
            }
            return neg ? -val : val;
        };
        auto skipWhite = [&]() {
            while (line[i] == ' ') ++i;
        };
        segs.emplace_back();
        segs.back().x = next(','); ++i; skipWhite();
        segs.back().y = next(','); ++i; skipWhite();
        segs.back().z = next(' '); i += 2; skipWhite();
        segs.back().vx = next(','); ++i; skipWhite();
        segs.back().vy = next(','); ++i; skipWhite();
        segs.back().vz = next(',');
    }
    return segs;
}

void partA() {
    vector<Segment> segs = readInput();
    const ld low = 200000000000000, high = 400000000000000;
    int count = 0;
    for (int i = 0; i < segs.size(); ++i) {
        for (int j = i+1; j < segs.size(); ++j) {
            Segment& p1 = segs[i];
            Segment& p2 = segs[j];
            auto cross = [](ld x1, ld y1, ld x2, ld y2) {
                return x1 * y2 - x2 * y1;
            };

            // d = p2 - p1
            ld dx = p2.x - p1.x;
            ld dy = p2.y - p1.y;

            // parallel check
            ld vCross = cross(p1.vx, p1.vy, p2.vx, p2.vy);
            if (vCross == 0) {
                // colinear check
                if (cross(dx, dy, p1.vx, p1.vy) == 0) {
                    cout << "COLINEAR NOT SUPPORTED" << endl;
                    exit(-1);
                }
                continue;
            }

            // t1 = (d x v2) / (v1 x v2)
            // t2 = (d x v1) / (v2 x v1)
            ld t1 = cross(dx, dy, p2.vx, p2.vy) / vCross;
            ld t2 = cross(-dx, -dy, p1.vx, p1.vy) / (-vCross);
            if (t1 < 0 || t2 < 0) continue;
            
            // intersection
            ld ix = p1.x + p1.vx * t1;
            ld iy = p1.y + p1.vy * t1;
            ix = p2.x + p2.vx * t2;
            iy = p2.y + p2.vy * t2;
            if (ix < low || iy < low || ix > high || iy > high) continue;
            ++count;
        }
    }
    cout << count << endl;
}

Eigen::Matrix3d crossMatrix(Eigen::Vector3d v)
{
    Eigen::Matrix3d result;
    result << 0, -v[2], v[1],
        v[2], 0, -v[0],
        -v[1], v[0], 0;
    return result;
}

void partB() {
    vector<Segment> segs = readInput();
    Segment rock;

    // eigen bs i copied from https://www.reddit.com/r/adventofcode/comments/18pnycy/comment/kepu26z/?utm_source=share&utm_medium=web2x&context=3
    // not solving this problem since most used a solver anyways
    Eigen::MatrixXd M(6, 6);
    Eigen::VectorXd rhs(6);
    auto segPoint = [&](int i) {
        return Eigen::Vector3d(segs[i].x, segs[i].y, segs[i].z);
    };
    auto segVelo = [&](int i) {
        return Eigen::Vector3d(segs[i].vx, segs[i].vy, segs[i].vz);
    };
    rhs.segment<3>(0) = -segPoint(0).cross(segVelo(0)) + segPoint(1).cross(segVelo(1));
    rhs.segment<3>(3) = -segPoint(0).cross(segVelo(0)) + segPoint(2).cross(segVelo(2));
    M.block<3, 3>(0, 0) = crossMatrix(segVelo(0)) - crossMatrix(segVelo(1));
    M.block<3, 3>(3, 0) = crossMatrix(segVelo(0)) - crossMatrix(segVelo(2));
    M.block<3, 3>(0, 3) = -crossMatrix(segPoint(0)) + crossMatrix(segPoint(1));
    M.block<3, 3>(3, 3) = -crossMatrix(segPoint(0)) + crossMatrix(segPoint(2));
    Eigen::Vector3d result = M.inverse() * rhs;
    ll sum = 0;
    for (int i = 0; i < 3; i++)
        sum += (ll)result[i];
    cout << sum << endl;
}


int main(int argc, char **argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);
    cout << setprecision(12);
    freopen("./input.txt","r",stdin);
    auto start = chrono::high_resolution_clock::now();
    argv[1][0] == 'A' ? partA() : partB();
    auto end = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>(end - start).count() << "microseconds" << endl;
}