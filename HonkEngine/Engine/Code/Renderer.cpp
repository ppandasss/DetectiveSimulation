	#include "Renderer.h"
	#include "Engine.h"



	void Renderer::Initialize(int width, int height)
	{
		m_windowWidth = width;
		m_windowHeight = height;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		const char* SHADER_VERTEX_PATH = "Assets/Shaders/color_tex_transparency.vert";
		const char* SHADER_FRAGMENT_PATH = "Assets/Shaders/color_tex_transparency.frag";
		m_shader.Initialize(SHADER_VERTEX_PATH, SHADER_FRAGMENT_PATH);
	}

	void Renderer::SetRenderMode(int mode, float alpha) {

		glViewport(0, 0, m_windowWidth, m_windowHeight);
		m_shader.use();  // Activate the shader
		m_shader.setInt("mode", mode);  // Set integer uniform
		m_shader.setFloat("alpha", alpha);  // Set float uniform

		// default setting
		//SetTexture(m_blankTex, 0.0f, 0.0f);
		//SetTransform(glm::mat4(1.0f));
	}

	void Renderer::SetTransform(const glm::mat4& modelMat) {

		Camera& camera = Application::GetCamera();
		//std::cout << "zoom: " << camera.GetZoom() << std::endl;
		cdt_MVP = camera.GetProjectionMatrix() * camera.GetViewMatrix()  * modelMat;
		m_shader.SetMatrix4("MVP", cdt_MVP);
		int errocode = glGetError();

		//std::cout << "Error code" << errocode << std::endl;
	}

	void Renderer::SetTexture(Tex tex, float offsetX, float offsetY) {

		//std::cout << "SetTexture::TextureID " << tex << std::endl;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		m_shader.setInt("tex1", 0);  // Set integer uniform
		m_shader.setFloat("offsetX", offsetX);  // Set float uniform
		m_shader.setFloat("offsetY", offsetY);  // Set float uniform
	}


	void Renderer::DrawMesh(const Mesh& mesh) {
		//std::cout << " DrawMesh method called:\n";

		glBindVertexArray(mesh.vaoHandle);
		glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size());

		glBindVertexArray(0);
	}

	void Renderer::UnloadMesh(Mesh& mesh)
	{
		glDeleteBuffers(1, &mesh.vertexBuffer);
		glDeleteVertexArrays(1, &mesh.vaoHandle);

		mesh.vertices.clear();
	}

	void Renderer::TextureUnload(Tex& tex)
	{
		glDeleteTextures(1, &tex);
		tex = GL_INVALID_INDEX;
	}

	void Renderer::SetTexturerColor(const glm::vec4& color)
	{
		m_shader.use();
		m_shader.SetVector4f("Color", color);
	}