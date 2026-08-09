/**
* @brief Represents an image.
 *
 * Stores the raw pixel data along with the image dimensions
 * and number of color channels.
 */
struct Image {
    /**
     * @brief Loads an image from disk.
     * @param filePath Path to the image file.
     * @param flip Whether to vertically flip the image when loading.
     */
    Image(const std::string& filePath, bool flip = false);

    /**
     * @brief Releases the image pixel data.
     */
    ~Image();

    unsigned char* Pixels = nullptr;

    /** Image width in pixels. */
    int Width = 0;

    /** Image height in pixels. */
    int Height = 0;

    /** Number of color channels per pixel. */
    int NrChannels = 0;
};
