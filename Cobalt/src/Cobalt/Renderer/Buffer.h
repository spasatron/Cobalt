#pragma once

namespace Cobalt {

	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {


		switch(type) {
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4*2;
		case ShaderDataType::Float3:	return 4*3;
		case ShaderDataType::Float4:	return 4*4;
		case ShaderDataType::Mat3:		return 4*3*3;
		case ShaderDataType::Mat4:		return 4*4*4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4*2;
		case ShaderDataType::Int3:		return 4*3;
		case ShaderDataType::Int4:		return 4*4;
		case ShaderDataType::Bool:		return 1;
		}
		COBALT_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	struct BufferElements {
		std::string name;
		uint32_t offset;
		uint32_t size;
		bool normalized;
		ShaderDataType type;

		BufferElements() {}
		BufferElements(ShaderDataType s_type, const std::string& s_name, bool norm = false) : name(s_name), type(s_type), size(ShaderDataTypeSize(s_type)), offset(0), normalized(norm){

		}

		uint32_t GetComponentCount() const {
			switch (type) {
			case ShaderDataType::Float:		
			case ShaderDataType::Int:		
			case ShaderDataType::Bool:		
				return 1;
			case ShaderDataType::Float2:
			case ShaderDataType::Int2:		
				return 2;
			case ShaderDataType::Float3:
			case ShaderDataType::Int3:		
				return 3;
			case ShaderDataType::Float4:
			case ShaderDataType::Int4:		
				return 4;
			case ShaderDataType::Mat3:		
				return 3 * 3;
			case ShaderDataType::Mat4:		
				return 4 * 4;
			}
			COBALT_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}

	};

	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElements>& layout) : m_elements(layout) {
		
			CalculateOffsetsAndStride();
		}
		inline uint32_t GetStride() const { return m_stride; }
		inline const std::vector<BufferElements>& GetElements() const { return m_elements; }
		std::vector<BufferElements>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElements>::iterator end() { return m_elements.end(); }
		std::vector<BufferElements>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElements>::const_iterator end() const { return m_elements.end(); }

	private:
		void CalculateOffsetsAndStride() {
			uint32_t s_offset = 0;
			m_stride = 0;
			for (auto& elements : m_elements) {
				elements.offset = s_offset;
				s_offset += elements.size;
				m_stride += elements.size;
			}
		}
	private:
		std::vector<BufferElements> m_elements;
		uint32_t m_stride = 0;
	};

	//Both classes here are almost like a v-table, no data members are stored here. Inherited classes will decide the actual implementation





	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}


		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);


	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}


		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);

	};


}
