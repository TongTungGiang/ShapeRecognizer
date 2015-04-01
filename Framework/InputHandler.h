//------------------------------------------------------------------------------------------
//
//  InputHandler.h
//
//  Created by CNTA.C++ Team in 2014
//
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL/SDL.h>
#include <functional>

#define fw_getFunctionAddress(f) std::bind(&f, this)

namespace Framework
{

	typedef void fw_Callback;

	enum event_type
	{
		FW_EVENT_QUIT,
		FW_EVENT_LEFT_MOUSE_BUTTON_UP,
		FW_EVENT_LEFT_MOUSE_BUTTON_DOWN,
		FW_EVENT_RIGHT_MOUSE_BUTTON_UP,
		FW_EVENT_RIGHT_MOUSE_BUTTON_DOWN,
		FW_EVENT_MIDDLE_MOUSE_BUTTON_UP,
		FW_EVENT_MIDDLE_MOUSE_BUTTON_DOWN,
		FW_EVENT_MOUSE_MOVE
	};

	class InputHandler
	{
	private:
		static  InputHandler* singleton;

		static int xMouse;
		static int yMouse;

		static bool isStringCapturing;
		static std::string receptedCharacters;
		static std::string* stringPointer;
		static unsigned int maxStringLength;

		static std::function<void()> quit_callback;
		static std::function<void()> leftMouseButtonsUp_callback;
		static std::function<void()> leftMouseButtonsDown_callback;
		static std::function<void()> rightMouseButtonsUp_callback;
		static std::function<void()> rightMouseButtonsDown_callback;
		static std::function<void()> middleMouseButtonsUp_callback;
		static std::function<void()> middleMouseButtonsDown_callback;
		static std::function<void()> mouseMove_callback;

		InputHandler() {};

	public:
		static InputHandler* instance()
		{
			if (!singleton)
			{
				singleton = new InputHandler();
			}
			return singleton;
		}

		void fwi_initialize();

		/*
		Lấy tọa độ con trỏ chuột trong cửa sổ chương trình.

		Các tham số:
		-	x: con trỏ tới vùng nhớ nhận giá trị tọa độ theo trục x
		-	y: con trỏ tới vùng nhớ nhận giá trị tọa độ theo trục y
		*/
		void fwi_getMousePosition(int* x, int* y);

		/*
		Thiết lập callback function ứng với các sự kiện chuột, bàn phím, ...
		phục vụ cho việc thực thi của hàm fwi_PollEvent().

		Các tham số
		-	event_type: loại sự kiện (được định nghĩa bởi các hằng có tiền tố FW_EVENT_)
		-	function_pointer: con trỏ tới hàm sẽ được thiết lập làm callback function.

		CHÚ Ý:
		-	Hàm được thiết lập làm callback function phải có kiểu là void,
		không được có bất kỳ tham số nào.
		-	Thiết lập lại callback function ứng với một sự kiện sẽ thay thế function
		được thiết lập trước lần đó.
		-	Để đơn giản, sử dụng macro fw_getFunctionAddress(f) cho đối số ứng với
		function_pointer, với f là tên của hàm được thiết lập làm callback function
		(hàm này phải là hàm thành viên của class chứa object gọi đến macro này).
		*/
		//void fwi_setCallbackFunction(unsigned int event_type, std::function<fw_Callback()>  const &function_pointer);
		void fwi_setCallbackFunction(unsigned int event_type, std::function<void()> function_pointer);

		/*
		Thực hiện duyệt toàn bộ hàng đợi sự kiện và gọi các callback function tương ứng
		đã được thiết lập bởi hàm fwi_setCallbackFunction.

		Hàng đợi sự kiện chứa tất cả các sự kiện xảy ra từ lần gọi hàm này trước đó.

		Các sự kiện bao gồm:
		-	phím chuột bị nhấn/nhả
		-	bàn phím bị nhấn/nhả
		-	cửa sổ chương trình bị đóng lại
		*/
		void fwi_PollEvent();

		void fwi_startStringCapture(std::string receptedCharacters);
		void fwi_setCapturedString(std::string* str, int maxStringLength);
		void fwi_stopStringCapture();
		void fwi_resetCallback();
		void fwi_destroy();
	};

}

#endif