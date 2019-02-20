#include "BarcodeFormat.h"
#include "DecodeHints.h"
#include "MultiFormatReader.h"
#include "GenericLuminanceSource.h"
#include "HybridBinarizer.h"
#include "Result.h"
#include "ResultMetadata.h"
#include "TextUtfEncoding.h"

#include "oned/ODReader.h"
#include "qrcode/QRReader.h"
#include "datamatrix/DMReader.h"
#include "aztec/AZReader.h"
#include "maxicode/MCReader.h"
#include "pdf417/PDFReader.h"

#include <memory>
#include <unordered_set>

#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

extern "C"  //Tells the compile to use C-linkage for the next scope.
{
    int DecodePDF417(void *barcode, int width, int height, char *decoded)
    {

        try
        {
            ZXing::DecodeHints hints;
            hints.setShouldTryHarder(true);
            hints.setShouldTryRotate(false);
            auto format = ZXing::BarcodeFormatFromString("PDF_417");
            hints.setPossibleFormats({ format });
            ZXing::MultiFormatReader reader(hints);
            ZXing::GenericLuminanceSource source(width, height, barcode, width);
            ZXing::HybridBinarizer binImage(std::shared_ptr<ZXing::LuminanceSource>(&source, [](void*) {}));
            auto result = reader.read(binImage);
            if (result.isValid()) {
                auto s = ZXing::TextUtfEncoding::ToUtf8(result.text());
                strncpy(decoded, s.c_str(), 1999);
                return 0;
            }
            return -1;
        }
        catch(...)
        {
            return -2;
        }
    }

}
