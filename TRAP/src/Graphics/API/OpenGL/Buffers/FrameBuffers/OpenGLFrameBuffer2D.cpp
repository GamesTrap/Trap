#include "TRAPPCH.h"

#include "OpenGLFrameBuffer2D.h"
#include "Graphics/API/OpenGL/OpenGLCommon.h"

const TRAP::Graphics::API::OpenGLFrameBuffer2D* TRAP::Graphics::API::OpenGLFrameBuffer2D::s_currentlyBound = nullptr;

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Graphics::API::OpenGLFrameBuffer2D::OpenGLFrameBuffer2D(const uint32_t width, const uint32_t height)
	: m_frameBufferHandle(0), m_depthBufferHandle(0), m_width(width), m_height(height)
{
	Init();
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Graphics::API::OpenGLFrameBuffer2D::~OpenGLFrameBuffer2D()
{
	if(s_currentlyBound == this)
	{
		Unbind();
		if(m_frameBufferHandle)
		{
			OpenGLCall(glDeleteFramebuffers(1, &m_frameBufferHandle));		
		}
		if(m_depthBufferHandle)
		{
			OpenGLCall(glDeleteRenderbuffers(1, &m_depthBufferHandle));
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::OpenGLFrameBuffer2D::Init()
{
	OpenGLCall(glCreateFramebuffers(1, &m_frameBufferHandle));
	OpenGLCall(glCreateRenderbuffers(1, &m_depthBufferHandle));

	m_texture = Texture2D::CreateEmpty(ImageFormat::RGBA, m_width, m_height, {TextureFilter::Linear, TextureWrap::Clamp_To_Edge});
	OpenGLCall(glNamedFramebufferTexture(m_frameBufferHandle, GL_COLOR_ATTACHMENT0, (dynamic_cast<OpenGLTexture2D*>(m_texture.get()))->GetHandle(), 0));

	OpenGLCall(glNamedRenderbufferStorage(m_depthBufferHandle, GL_DEPTH_COMPONENT16, m_width, m_height));
	OpenGLCall(glNamedFramebufferRenderbuffer(m_frameBufferHandle, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferHandle));

	OpenGLCall(glCheckNamedFramebufferStatus(m_frameBufferHandle, GL_FRAMEBUFFER));
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::OpenGLFrameBuffer2D::Bind() const
{
	if(s_currentlyBound != this)
	{
		OpenGLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle));
		s_currentlyBound = this;
		OpenGLCall(glViewport(0, 0, m_width, m_height));		
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::OpenGLFrameBuffer2D::Unbind() const
{
	if(s_currentlyBound)
	{
		OpenGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		s_currentlyBound = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::OpenGLFrameBuffer2D::SetClearColor(const Math::Vec4& color)
{
	if(s_currentlyBound == this)
	{
		OpenGLCall(glClearColor(color.x, color.y, color.z, color.w));
	}
	else
	{
		Bind();
		OpenGLCall(glClearColor(color.x, color.y, color.z, color.w));
		Unbind();
	}
}


//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::OpenGLFrameBuffer2D::Clear()
{
	if (s_currentlyBound == this)
	{
		OpenGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
	else
	{
		Bind();
		OpenGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		Unbind();
	}	
}