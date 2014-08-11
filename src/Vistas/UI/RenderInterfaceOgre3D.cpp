/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "RenderInterfaceOgre3D.h"
//#include "OgreFramework.h"
//#include <Ogre.h>

struct RocketOgre3DVertex
{
	float x, y, z;
	Ogre::uint32 diffuse;
	float u, v;
};

// The structure created for each texture loaded by Rocket for Ogre.
struct RocketOgre3DTexture
{
	RocketOgre3DTexture(Ogre::TexturePtr texture) : texture(texture)
	{
	}

	Ogre::TexturePtr texture;
};

// The structure created for each set of geometry that Rocket compiles. It stores the vertex and index buffers and the
// texture associated with the geometry, if one was specified.
struct RocketOgre3DCompiledGeometry
{
	Ogre::RenderOperation render_operation;
	RocketOgre3DTexture* texture;
};

RenderInterfaceOgre3D::RenderInterfaceOgre3D(unsigned int window_width, unsigned int window_height)
{



	hecho = false;

	projection_matrix = Ogre::Matrix4::ZERO;
	render_system = Ogre::Root::getSingleton().getRenderSystem();

	
	// Configure the colour blending mode.
	colour_blend_mode.blendType = Ogre::LBT_COLOUR;
	colour_blend_mode.source1 = Ogre::LBS_DIFFUSE;
	colour_blend_mode.source2 = Ogre::LBS_TEXTURE;
	colour_blend_mode.operation = Ogre::LBX_MODULATE;

	// Configure the alpha blending mode.
	alpha_blend_mode.blendType = Ogre::LBT_ALPHA;
	alpha_blend_mode.source1 = Ogre::LBS_DIFFUSE;
	alpha_blend_mode.source2 = Ogre::LBS_TEXTURE;
	alpha_blend_mode.operation = Ogre::LBX_MODULATE;

	scissor_enable = false;

	scissor_left = 0;
	scissor_top = 0;
	scissor_right = (int) window_width;
	scissor_bottom = (int) window_height;
	   
  mWindowWidth = window_width;
   mWindowHeight = window_height;


	//customProjectionMatrix = Ogre::Matrix4::IDENTITY;

											
		CreateShader();


}

RenderInterfaceOgre3D::~RenderInterfaceOgre3D()
{

render_system = NULL;

}

// Called by Rocket when it wants to render geometry that it does not wish to optimise.
void RenderInterfaceOgre3D::RenderGeometry(Rocket::Core::Vertex* ROCKET_UNUSED_PARAMETER(vertices), int ROCKET_UNUSED_PARAMETER(num_vertices), int* ROCKET_UNUSED_PARAMETER(indices), int ROCKET_UNUSED_PARAMETER(num_indices), Rocket::Core::TextureHandle ROCKET_UNUSED_PARAMETER(texture), const Rocket::Core::Vector2f& ROCKET_UNUSED_PARAMETER(translation))
{

	// We've chosen to not support non-compiled geometry in the Ogre3D renderer.
}

// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
Rocket::Core::CompiledGeometryHandle RenderInterfaceOgre3D::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture)
{

	RocketOgre3DCompiledGeometry* geometry = new RocketOgre3DCompiledGeometry();
	geometry->texture = texture == NULL ? NULL : (RocketOgre3DTexture*) texture;

	geometry->render_operation.vertexData = new Ogre::VertexData();
	geometry->render_operation.vertexData->vertexStart = 0;
	geometry->render_operation.vertexData->vertexCount = num_vertices;

	geometry->render_operation.indexData = new Ogre::IndexData();
	geometry->render_operation.indexData->indexStart = 0;
	geometry->render_operation.indexData->indexCount = num_indices;

	geometry->render_operation.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;


	// Set up the vertex declaration.
	Ogre::VertexDeclaration* vertex_declaration = geometry->render_operation.vertexData->vertexDeclaration;
	size_t element_offset = 0;
	vertex_declaration->addElement(0, element_offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	element_offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
	vertex_declaration->addElement(0, element_offset, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
	element_offset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
	vertex_declaration->addElement(0, element_offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);

	// Create the vertex buffer.
	Ogre::HardwareVertexBufferSharedPtr vertex_buffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(vertex_declaration->getVertexSize(0), num_vertices, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
	geometry->render_operation.vertexData->vertexBufferBinding->setBinding(0, vertex_buffer);

	// Fill the vertex buffer.
	RocketOgre3DVertex* ogre_vertices = (RocketOgre3DVertex*) vertex_buffer->lock(0, vertex_buffer->getSizeInBytes(), Ogre::HardwareBuffer::HBL_NORMAL);
	for (int i = 0; i < num_vertices; ++i)
	{
		ogre_vertices[i].x = vertices[i].position.x;
		ogre_vertices[i].y = vertices[i].position.y;
		ogre_vertices[i].z = 0;

		Ogre::ColourValue diffuse(vertices[i].colour.red / 255.0f, vertices[i].colour.green / 255.0f, vertices[i].colour.blue / 255.0f, vertices[i].colour.alpha / 255.0f);
		render_system->convertColourValue(diffuse, &ogre_vertices[i].diffuse);

		ogre_vertices[i].u = vertices[i].tex_coord[0];
		ogre_vertices[i].v = vertices[i].tex_coord[1];
	}
	vertex_buffer->unlock();

	// Create the index buffer.
#if OGRE_PLATFORM == OGRE_PLATFORM_IOS || OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
	Ogre::HardwareIndexBufferSharedPtr index_buffer = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT, num_indices, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
#else
	Ogre::HardwareIndexBufferSharedPtr index_buffer = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(Ogre::HardwareIndexBuffer::IT_32BIT, num_indices, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
#endif
	geometry->render_operation.indexData->indexBuffer = index_buffer;
	geometry->render_operation.useIndexes = true;

	// Fill the index buffer.
#if OGRE_PLATFORM == OGRE_PLATFORM_IOS || OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
	uint16_t* ogre_indices = (uint16_t*) index_buffer->lock(0, index_buffer->getSizeInBytes(), Ogre::HardwareBuffer::HBL_NORMAL);
	for (int i = 0; i < num_indices; ++i)
    {
		ogre_indices[i] = indices[i];
	}
#else
	void* ogre_indices = index_buffer->lock(0, index_buffer->getSizeInBytes(), Ogre::HardwareBuffer::HBL_NORMAL);
	memcpy(ogre_indices, indices, sizeof(unsigned int) * num_indices);
#endif
	index_buffer->unlock();
	
	Rocket::Core::CompiledGeometryHandle compiledGeometry = 0;
	compiledGeometry = reinterpret_cast<Rocket::Core::CompiledGeometryHandle>(geometry);
	if( !compiledGeometry )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage( "libRocket: Failed to compile geometry -- Line 160 -- RenderInterfaceOgre3D.cpp" );
	}

	return compiledGeometry;
}

void RenderInterfaceOgre3D::CreateShader()
{

   mVertexProgram = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram("SimpleTexturingNoLightsVP",
                                                            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
#if OGRE_PLATFORM == OGRE_PLATFORM_IOS || OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
                                                            "glsles",
#else
															"glsl",
#endif
                                                            Ogre::GPT_VERTEX_PROGRAM);
   #if OGRE_PLATFORM == OGRE_PLATFORM_IOS || OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
   mVertexProgram->setSourceFile( "rocket_vp.glsles" );
   #else
    mVertexProgram->setSourceFile( "rocket_vp.glsl" );
   #endif
   mVertexProgram->load();
   mVertexProgramParams = mVertexProgram->getDefaultParameters();

   mFragmentProgram = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram("SimpleTexturingNoLightsFP",
                                                            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
#if OGRE_PLATFORM == OGRE_PLATFORM_IOS || OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
                                                            "glsles",
#else
															"glsl",
#endif
                                                            Ogre::GPT_FRAGMENT_PROGRAM);

#if OGRE_PLATFORM == OGRE_PLATFORM_IOS || OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
   mFragmentProgram->setSourceFile( "rocket_fp.glsles" );
#else
   mFragmentProgram->setSourceFile( "rocket_fp.glsl" );
#endif
   mFragmentProgram->load();
   mFragmentProgramParams = mFragmentProgram->getDefaultParameters();







}

// Called by Rocket when it wants to render application-compiled geometry.
void RenderInterfaceOgre3D::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
{

   render_system = Ogre::Root::getSingleton().getRenderSystem();
     
	   
	// Load the blank 1x1 texture used for colour pass through
	/*Ogre::TextureManager* texture_manager = Ogre::TextureManager::getSingletonPtr();
	m_blankTexture = texture_manager->load("blank.png",
											"General",
											Ogre::TEX_TYPE_2D,
											0);	 

*/
	 render_system->bindGpuProgram( mVertexProgram->_getBindingDelegate() );
     render_system->bindGpuProgram( mFragmentProgram->_getBindingDelegate() );

     //  Ogre::Matrix4 transform;
      // transform.makeTrans(translation.x, translation.y, 0);
     //  render_system->_setWorldMatrix(transform);

   //Ogre::Matrix4 projection_matrix;
   
   

	RocketOgre3DCompiledGeometry* ogre3d_geometry = (RocketOgre3DCompiledGeometry*)geometry;

	if (ogre3d_geometry->texture != NULL)
	{

		render_system->_setTexture(0, true, ogre3d_geometry->texture->texture);

          // ADD THIS LINE:
          render_system->_setTextureUnitFiltering(0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_POINT);
          // Ogre can change the blending modes when textures are disabled - so in case the last render had no texture,
          // we need to re-specify them.
         // render_system->_setTextureBlendMode(0, colour_blend_mode);
          //render_system->_setTextureBlendMode(0, alpha_blend_mode);
	}
	else
	{

            // ADD THIS LINE:
          render_system->_setTextureUnitFiltering(0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_POINT);
          // render_system->_disableTextureUnit(0);

		// Background elements don't use textures, and just have a pure colour element. So, rather than creating a different shader
		// for colour pass-through, just have the fragment shader sample a 1x1 texture with colour values of ( 1.0, 1.0, 1.0, 1.0 )
		//render_system->_setTexture( 0, true, m_blankTexture );
	}

	if  (projection_matrix == Ogre::Matrix4::ZERO)
{
 BuildProjectionMatrix(projection_matrix);
 //render_system->_setProjectionMatrix(projection_matrix);

}

  Ogre::Matrix4 model;

	model.makeTrans(translation.x, translation.y, 0);

	Ogre::Matrix4 viewProjMatrix = projection_matrix * model;


	//Ogre::GpuProgramParametersSharedPtr params = mVertexProgram->getDefaultParameters();
	mVertexProgramParams->setNamedConstant( "modelViewProj", &viewProjMatrix, 1 );

	//if (!hecho)
	//{
	 
	
   //mVertexProgramParams->setNamedConstant("modelViewProj",  projection_matrix * model);
 //  mVertexProgramParams->get


   render_system->bindGpuProgramParameters(Ogre::GPT_VERTEX_PROGRAM, mVertexProgramParams, Ogre::GPV_ALL);
	
	
	//}


//mVertexProgramParams->getConstan








	/* Ogre::HighLevelGpuProgramPtr vertProg;
     Ogre::HighLevelGpuProgramPtr fragProg;

	 vertProg = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram("SimpleTexturingNoLightsVP",
                                                                              Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                                              "glsles",
                                                                              Ogre::GPT_VERTEX_PROGRAM);
    vertProg->setSourceFile( "rocket_vp.glsles" );
    vertProg->load();
    
    fragProg = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram("SimpleTexturingNoLightsFP",
                                                                              Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                                              "glsles",
                                                                              Ogre::GPT_FRAGMENT_PROGRAM);
    fragProg->setSourceFile( "rocket_fp.glsles" );
    fragProg->load();




	// render_system->bindGpuProgram( vertProg->_getBindingDelegate() );
   //  render_system->bindGpuProgram( fragProg->_getBindingDelegate() );


	
	Ogre::GpuProgramPtr vpShader = Ogre::HighLevelGpuProgramManager::getSingletonPtr()->getByName( "RocketVP_GLSL" );
	Ogre::GpuProgramPtr fpShader = Ogre::HighLevelGpuProgramManager::getSingletonPtr()->getByName( "RocketFP_GLSL" );

	Ogre::Matrix4 model;
	model.makeTrans(translation.x, translation.y, 0);

	Ogre::Matrix4 viewProjMatrix = customProjectionMatrix * model;

	Ogre::GpuProgramParametersSharedPtr params = vpShader->getDefaultParameters();
	params->setNamedConstant( "modelViewProj", &viewProjMatrix, 1 );

	Ogre::GpuProgram *vpBindingShader = vpShader->_getBindingDelegate();
	Ogre::GpuProgram *fpBindingShader = fpShader->_getBindingDelegate();

	render_system->bindGpuProgram( vpShader.get());//vpBindingShader );
	render_system->bindGpuProgram( fpShader.get());//fpBindingShader );

	render_system->bindGpuProgramParameters( Ogre::GPT_VERTEX_PROGRAM, params, Ogre::GPV_GLOBAL );
	*/

	render_system->_render( ogre3d_geometry->render_operation );

}

// Called by Rocket when it wants to release application-compiled geometry.
void RenderInterfaceOgre3D::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
           //     std::cout << "ReleaseCompiledGeometry!!!! "<<std::endl;


    RocketOgre3DCompiledGeometry* ogre3d_geometry = reinterpret_cast<RocketOgre3DCompiledGeometry*>(geometry);
	delete ogre3d_geometry->render_operation.vertexData;
	delete ogre3d_geometry->render_operation.indexData;
	delete ogre3d_geometry;
}

// Called by Rocket when it wants to enable or disable scissoring to clip content.
void RenderInterfaceOgre3D::EnableScissorRegion(bool enable)
{

	scissor_enable = enable;

	if (!scissor_enable)
		render_system->setScissorTest(false);
	else
		render_system->setScissorTest(true, scissor_left, scissor_top, scissor_right, scissor_bottom);
}

// Called by Rocket when it wants to change the scissor region.
void RenderInterfaceOgre3D::SetScissorRegion(int x, int y, int width, int height)
{

	scissor_left = x;
	scissor_top = y;
	scissor_right = x + width;
	scissor_bottom = y + height;

	if (scissor_enable)
		render_system->setScissorTest(true, scissor_left, scissor_top, scissor_right, scissor_bottom);
}

// Called by Rocket when a texture is required by the library.
bool RenderInterfaceOgre3D::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{

	Ogre::LogManager::getSingletonPtr()->logMessage( "loadtex"+Ogre::String(source.CString()) );
	int pos = source.RFind("/");
   pos++;
   Rocket::Core::String fileName(source.Substring(pos));
	Ogre::TextureManager* texture_manager = Ogre::TextureManager::getSingletonPtr();
   Ogre::TexturePtr ogre_texture = texture_manager->getByName(Ogre::String(fileName.CString()));
	if (ogre_texture.isNull())
	{
		Ogre::LogManager::getSingletonPtr()->logMessage( " loading rocket texture:" + Ogre::String(fileName.CString()));
		ogre_texture = texture_manager->load(Ogre::String(fileName.CString()),
											 "Rocket",
											 Ogre::TEX_TYPE_2D,
											 0);
	}

	if (ogre_texture.isNull())
	{
		Ogre::LogManager::getSingletonPtr()->logMessage( " Failed to load" );
		return false;
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage( "Loaded ok good! yay!" );
	}

	texture_dimensions.x = ogre_texture->getWidth();
	texture_dimensions.y = ogre_texture->getHeight();

	texture_handle = reinterpret_cast<Rocket::Core::TextureHandle>(new RocketOgre3DTexture(ogre_texture));
	return true;
}

// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
bool RenderInterfaceOgre3D::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{

	bool result = true;
	Ogre::LogManager::getSingletonPtr()->logMessage( "libRocket: Generating texture" );
	static int texture_id = 1;
	Ogre::DataStreamPtr dataStream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream((void*) source, source_dimensions.x * source_dimensions.y * sizeof(unsigned int)));
	Ogre::TexturePtr ogre_texture = Ogre::TextureManager::getSingleton().loadRawData(Rocket::Core::String(16, "%d", texture_id++).CString(),
																					 "Rocket",
																					 dataStream,
                                                                    (Ogre::ushort)source_dimensions.x,
                                                                    (Ogre::ushort)source_dimensions.y,
                                                                    Ogre::PF_A8B8G8R8,
                                                                    //Ogre::PF_A8B8G8R8,
																					 Ogre::TEX_TYPE_2D,
																					 0);

	if (ogre_texture.isNull())
	{
		result = false;
		Ogre::LogManager::getSingletonPtr()->logMessage( "libRocket: Failed to generate texture" );
	}
	else
	{
		texture_handle = reinterpret_cast<Rocket::Core::TextureHandle>(new RocketOgre3DTexture(ogre_texture));
          Ogre::LogManager::getSingletonPtr()->logMessage( "libRocket: texture generated ok good #1" );
	}
	
	return result;
}

// Called by Rocket when a loaded texture is no longer required.
void RenderInterfaceOgre3D::ReleaseTexture(Rocket::Core::TextureHandle texture)
{

	delete ((RocketOgre3DTexture*) texture);
}

// Returns the native horizontal texel offset for the renderer.
float RenderInterfaceOgre3D::GetHorizontalTexelOffset()
{
	return -render_system->getHorizontalTexelOffset();
}

// Returns the native vertical texel offset for the renderer.
float RenderInterfaceOgre3D::GetVerticalTexelOffset()
{
	return -render_system->getVerticalTexelOffset();
}

// Builds an OpenGL-style orthographic projection matrix.
void RenderInterfaceOgre3D::BuildProjectionMatrix(Ogre::Matrix4& projection_matrix)
{
   float z_near = -1;
   float z_far = 1;

   projection_matrix = Ogre::Matrix4::ZERO;

   // Set up matrices.
   projection_matrix[0][0] = 2.0f / mWindowWidth;
   projection_matrix[0][3]= -1.0000000f;
   projection_matrix[1][1]= -2.0f / mWindowHeight;
   projection_matrix[1][3]= 1.0000000f;
   projection_matrix[2][2]= -2.0f / (z_far - z_near);
   projection_matrix[3][3]= 1.0000000f;
}

