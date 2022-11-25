#include "TestTexture2D.h"

namespace test {
	TestTexture2D::TestTexture2D()
		:m_Proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)), 
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_TranslationA(1, 1, 0),m_TranslationB(-1, -1, 0)
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		float positions[] = {
			// positions //texture coords
			 0.5f, -0.5f, 1.0f, 0.0f, //0
			 0.5f,  0.5f, 1.0f, 1.0f, //1
			-0.5f,  0.5f, 0.0f, 1.0f, //2
			-0.5f, -0.5f, 0.0f, 0.0f  //3
		};
		unsigned int indices[] =
		{
			0,1,2,
			2,3,0
		};

		m_VAO = std::make_unique<VertexArrary>();
		m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);
		m_VAO->AddBuffer(*m_VBO, layout);
		m_IBO = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shaders/basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
		m_Texture = std::make_unique<Texture>("res/textures/ChernoLogo.png");
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		Renderer renderer;
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, -1.0f, 1.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}