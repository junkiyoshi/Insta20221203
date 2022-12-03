#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(0.5);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 3);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();
	this->frame.clear();

	for (int radius = 50; radius <= 300; radius += 10) {

		for (int i = 0; i < this->triangle_list.size(); i++) {

			glm::vec3 avg = (this->triangle_list[i].getVertex(0) + this->triangle_list[i].getVertex(1) + this->triangle_list[i].getVertex(2)) / 3;
			avg = glm::normalize(avg) * radius;
			auto noise_value = ofNoise(avg.x * 0.0065, avg.y * 0.0065 + ofGetFrameNum() * 0.03, avg.z * 0.0065);
			if (noise_value < 0.45) { continue; }
			
			vector<glm::vec3> vertices;

			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(0)) * (radius + 5) - avg);
			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(1)) * (radius + 5) - avg);
			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(2)) * (radius + 5) - avg);

			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(0)) * (radius - 5) - avg);
			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(1)) * (radius - 5) - avg);
			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(2)) * (radius - 5) - avg);

			for (auto& vertex : vertices) {

				vertex += avg;
			}

			this->mesh.addVertices(vertices);
			this->frame.addVertices(vertices);

			ofColor mesh_color;
			mesh_color.setHsb(230, 200, ofMap(radius, 50, 300, 0, 255));

			for (int k = 0; k < vertices.size(); k++) {

				this->mesh.addColor(mesh_color);
				this->frame.addColor(ofColor(255, radius > 100 ? ofMap(radius, 100, 300, 0, 255) : 0));
			}

			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3);
			this->mesh.addTriangle(this->mesh.getNumVertices() - 4, this->mesh.getNumVertices() - 5, this->mesh.getNumVertices() - 6);

			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 5);
			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 5, this->mesh.getNumVertices() - 4);

			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 3, this->mesh.getNumVertices() - 6);
			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 6, this->mesh.getNumVertices() - 4);

			this->mesh.addTriangle(this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3, this->mesh.getNumVertices() - 6);
			this->mesh.addTriangle(this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 6, this->mesh.getNumVertices() - 5);

			this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 2);
			this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 3);
			this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 3);

			this->frame.addIndex(this->frame.getNumVertices() - 4); this->frame.addIndex(this->frame.getNumVertices() - 5);
			this->frame.addIndex(this->frame.getNumVertices() - 5); this->frame.addIndex(this->frame.getNumVertices() - 6);
			this->frame.addIndex(this->frame.getNumVertices() - 4); this->frame.addIndex(this->frame.getNumVertices() - 6);

			this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 4);
			this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 5);
			this->frame.addIndex(this->frame.getNumVertices() - 3); this->frame.addIndex(this->frame.getNumVertices() - 6);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.666666666666666);

	this->mesh.drawFaces();
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}