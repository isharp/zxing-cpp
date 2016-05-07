#pragma once
/*
* Copyright 2016 ZXing authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <string>
#include <memory>

namespace Gdiplus {
	class Bitmap;
}

namespace ZXing {

class MultiFormatReader;

class BarcodeScanner
{
public:
	struct ScanResult {
		std::string format;
		std::string text;
	};

	explicit BarcodeScanner(bool tryHarder = false, bool autoRotate = false);
	BarcodeScanner(const BarcodeScanner &) = delete;
	BarcodeScanner& operator=(const BarcodeScanner &) = delete;

	ScanResult scan(Gdiplus::Bitmap& bitmap);

private:
	std::shared_ptr<MultiFormatReader> _reader;
	bool _autoRotate;
};

} // ZXing