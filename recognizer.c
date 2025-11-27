#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Complete function at the top
int is_printable_ascii(const unsigned char *buffer, size_t len) {
    for (size_t i = 0; i < len; i++) {
        // Printable ASCII: 9-13 (tabs, newlines), 32-126 (printable chars)
        if (buffer[i] < 9 || (buffer[i] > 13 && buffer[i] < 32) || buffer[i] > 126) {
            return 0;
        }
    }
    return 1;
}

// Return file extension (including leading dot) on match, NULL on error/unknown
const char *file_recognizer(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    unsigned char buffer[16];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    if (bytesRead < 4) {
        return NULL;
    }

    // Images
    // PNG
    if (buffer[0] == 0x89 && buffer[1] == 0x50 && buffer[2] == 0x4E &&
        buffer[3] == 0x47 && buffer[4] == 0x0D && buffer[5] == 0x0A &&
        buffer[6] == 0x1A && buffer[7] == 0x0A) {
        return ".png";
    }

    // JPEG
    if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF) {
        return ".jpg";
    }

    // GIF
    if ((buffer[0] == 'G' && buffer[1] == 'I' && buffer[2] == 'F' &&
         buffer[3] == '8' && (buffer[4] == '7' || buffer[4] == '9') &&
         buffer[5] == 'a')) {
        return ".gif";
    }

    // BMP
    if (buffer[0] == 0x42 && buffer[1] == 0x4D) {
        return ".bmp";
    }

    // TIFF (little-endian)
    if (buffer[0] == 0x49 && buffer[1] == 0x49 &&
        buffer[2] == 0x2A && buffer[3] == 0x00) {
        return ".tiff";
    }

    // ICO
    if (buffer[0] == 0x00 && buffer[1] == 0x00 &&
        buffer[2] == 0x01 && buffer[3] == 0x00) {
        return ".ico";
    }

    // PSD
    if (buffer[0] == 0x38 && buffer[1] == 0x42 &&
        buffer[2] == 0x50 && buffer[3] == 0x53) {
        return ".psd";
    }

    // Audio
    // WAV / RIFF-based (heuristic)
    if (buffer[0] == 0x52 && buffer[1] == 0x49 &&
        buffer[2] == 0x46 && buffer[3] == 0x46) {
        // ambiguous RIFF container; return generic .wav as a common RIFF audio container
        return ".wav";
    }

    // OGG
    if (buffer[0] == 0x4F && buffer[1] == 0x67 &&
        buffer[2] == 0x67 && buffer[3] == 0x53) {
        return ".ogg";
    }

    // FLAC
    if (buffer[0] == 0x66 && buffer[1] == 0x4C &&
        buffer[2] == 0x61 && buffer[3] == 0x43) {
        return ".flac";
    }

    // MP3 (ID3)
    if (buffer[0] == 0x49 && buffer[1] == 0x44 &&
        buffer[2] == 0x33) {
        return ".mp3";
    }

    // Video
    // MPEG (system stream)
    if (buffer[0] == 0x00 && buffer[1] == 0x00 &&
        buffer[2] == 0x01 && buffer[3] == 0xBA) {
        return ".mpeg";
    }

    // MKV
    if (buffer[0] == 0x1A && buffer[1] == 0x45 &&
        buffer[2] == 0xDF && buffer[3] == 0xA3) {
        return ".mkv";
    }

    // MP4 / ISO Base Media file format (ftyp)
    if (buffer[0] == 0x00 && buffer[1] == 0x00 &&
        buffer[2] == 0x00 && (buffer[3] == 0x18 || buffer[3] == 0x20) &&
        buffer[4] == 0x66 && buffer[5] == 0x74 &&
        buffer[6] == 0x79 && buffer[7] == 0x70) {
        return ".mp4";
    }

    // Archives
    // ZIP
    if (buffer[0] == 0x50 && buffer[1] == 0x4B &&
       (buffer[2] == 0x03 || buffer[2] == 0x05 || buffer[2] == 0x07) &&
       (buffer[3] == 0x04 || buffer[3] == 0x06 || buffer[3] == 0x08)) {
        return ".zip";
    }

    // RAR
    if (buffer[0] == 0x52 && buffer[1] == 0x61 &&
        buffer[2] == 0x72 && buffer[3] == 0x21) {
        return ".rar";
    }

    // 7z
    if (buffer[0] == 0x37 && buffer[1] == 0x7A &&
        buffer[2] == 0xBC && buffer[3] == 0xAF &&
        buffer[4] == 0x27 && buffer[5] == 0x1C) {
        return ".7z";
    }

    // Compression
    if (buffer[0] == 0x1F && buffer[1] == 0x8B) {
        return ".gz";
    }
    if (buffer[0] == 0x42 && buffer[1] == 0x5A &&
        buffer[2] == 0x68) {
        return ".bz2";
    }

    // Executables
    // ELF
    if (buffer[0] == 0x7F && buffer[1] == 'E' && buffer[2] == 'L' &&
        buffer[3] == 'F') {
        return ".elf";
    }

    // PE (Windows) - 'MZ'
    if (buffer[0] == 'M' && buffer[1] == 'Z') {
        return ".exe";
    }

    // Mach-O (common magic)
    if (buffer[0] == 0xFE && buffer[1] == 0xED &&
        buffer[2] == 0xFA && buffer[3] == 0xCE) {
        return ".macho";
    }

    // Documents
    // PDF
    if (buffer[0] == 0x25 && buffer[1] == 0x50 && buffer[2] == 0x44 &&
        buffer[3] == 0x46) {
        return ".pdf";
    }

    // PostScript
    if (buffer[0] == 0x25 && buffer[1] == 0x21 &&
        buffer[2] == 0x50 && buffer[3] == 0x53) {
        return ".ps";
    }

    // RTF
    if (buffer[0] == 0x7B && buffer[1] == 0x5C &&
        buffer[2] == 0x72 && buffer[3] == 0x74 &&
        buffer[4] == 0x66) {
        return ".rtf";
    }

    // Microsoft Office (compound file / old formats)
    if (buffer[0] == 0xD0 && buffer[1] == 0xCF &&
        buffer[2] == 0x11 && buffer[3] == 0xE0) {
        return ".doc"; // old compound file formats (could be doc/xls/ppt)
    }

    // Fonts
    // TrueType
    if (buffer[0] == 0x00 && buffer[1] == 0x01 &&
        buffer[2] == 0x00 && buffer[3] == 0x00) {
        return ".ttf";
    }

    // OpenType (OTTO)
    if (buffer[0] == 0x4F && buffer[1] == 0x54 &&
        buffer[2] == 0x54 && buffer[3] == 0x4F) {
        return ".otf";
    }

    // WOFF
    if (buffer[0] == 0x77 && buffer[1] == 0x4F &&
        buffer[2] == 0x46 && buffer[3] == 0x46) {
        return ".woff";
    }

    // Database
    // SQLite
    if (buffer[0] == 0x53 && buffer[1] == 0x51 &&
        buffer[2] == 0x4C && buffer[3] == 0x69 &&
        buffer[4] == 0x74 && buffer[5] == 0x65) {
        return ".sqlite";
    }

    // LaTeX (heuristic)
    if (buffer[0] == 0x7B && buffer[1] == 0x5C &&
        buffer[2] == 0x70 && buffer[3] == 0x61 &&
        buffer[4] == 0x67 && buffer[5] == 0x65) {
        return ".tex";
    }

    // Misc / duplicates left as heuristics
    if (buffer[0] == 0x50 && buffer[1] == 0x4D) {
        return ".bin";
    }
    // ... your existing image, audio, video checks ...

    // TEXT FILES
    // UTF-8 BOM
    if (buffer[0] == 0xEF && buffer[1] == 0xBB && buffer[2] == 0xBF) {
        return ".txt";
    }
    
    // UTF-16 LE BOM
    if (buffer[0] == 0xFF && buffer[1] == 0xFE) {
        return ".txt";
    }
    
    // UTF-16 BE BOM
    if (buffer[0] == 0xFE && buffer[1] == 0xFF) {
        return ".txt";
    }
    
    // Plain text (heuristic - if first 8 bytes are printable ASCII)
    if (bytesRead >= 8 && is_printable_ascii(buffer, 8)) {
        return ".txt";
    }

    // CODE FILES
    // XML (starts with <?xml)
    if (buffer[0] == '<' && buffer[1] == '?' && buffer[2] == 'x' && 
        buffer[3] == 'm' && buffer[4] == 'l') {
        return ".xml";
    }
    
    // HTML (starts with <!DOCTYPE or <html)
    if ((buffer[0] == '<' && buffer[1] == '!' && buffer[2] == 'D' && 
         buffer[3] == 'O' && buffer[4] == 'C' && buffer[5] == 'T' && 
         buffer[6] == 'Y' && buffer[7] == 'P' && buffer[8] == 'E') ||
        (buffer[0] == '<' && buffer[1] == 'h' && buffer[2] == 't' && 
         buffer[3] == 'm' && buffer[4] == 'l')) {
        return ".html";
    }

    // JavaScript (common patterns)
    if ((buffer[0] == '/' && buffer[1] == '/') || 
        (buffer[0] == 'f' && buffer[1] == 'u' && buffer[2] == 'n' && buffer[3] == 'c' && buffer[4] == 't' && buffer[5] == 'i' && buffer[6] == 'o' && buffer[7] == 'n')) {
        return ".js";
    }

    // CSS
    if (buffer[0] == '/' && buffer[1] == '*' || 
        (buffer[0] == '@' && buffer[1] == 'i' && buffer[2] == 'm' && buffer[3] == 'p' && buffer[4] == 'o' && buffer[5] == 'r' && buffer[6] == 't')) {
        return ".css";
    }

    // C/C++ source
    if ((buffer[0] == '#' && buffer[1] == 'i' && buffer[2] == 'n' && buffer[3] == 'c' && buffer[4] == 'l' && buffer[5] == 'u' && buffer[6] == 'd' && buffer[7] == 'e') ||
        (buffer[0] == '/' && buffer[1] == '/') || 
        (buffer[0] == '/' && buffer[1] == '*')) {
        return ".c";
    }

    // Python
    if ((buffer[0] == '#' && buffer[1] == '!') ||
        (buffer[0] == 'd' && buffer[1] == 'e' && buffer[2] == 'f' ) ||
        (buffer[0] == 'i' && buffer[1] == 'm' && buffer[2] == 'p' && buffer[3] == 'o' && buffer[4] == 'r' && buffer[5] == 't' )) {
        return ".py";
    }

    // Java
    if ((buffer[0] == 'p' && buffer[1] == 'a' && buffer[2] == 'c' && buffer[3] == 'k' && buffer[4] == 'a' && buffer[5] == 'g' && buffer[6] == 'e') ||
        (buffer[0] == 'p' && buffer[1] == 'u' && buffer[2] == 'b' && buffer[3] == 'l' && buffer[4] == 'i' && buffer[5] == 'c')) {
        return ".java";
    }

    // SPREADSHEETS
    // Excel (older .xls format - compound file)
    if (buffer[0] == 0xD0 && buffer[1] == 0xCF && buffer[2] == 0x11 && buffer[3] == 0xE0) {
        return ".xls";
    }
    
    // Excel (newer .xlsx format - actually a zip file)
    if (buffer[0] == 0x50 && buffer[1] == 0x4B && buffer[2] == 0x03 && buffer[3] == 0x04) {
        // This could be any zip file, we'd need to check contents to be sure it's xlsx
        return ".xlsx";
    }

    // PRESENTATIONS
    // PowerPoint (older .ppt format - compound file)
    if (buffer[0] == 0xD0 && buffer[1] == 0xCF && buffer[2] == 0x11 && buffer[3] == 0xE0) {
        // Same magic as .doc and .xls, would need deeper inspection
        return ".ppt";
    }

    // ... rest of your existing code ...

    return NULL;
}
