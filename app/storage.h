#pragma once

#include <glib.h>

/* AX Storage library. */
#include <axsdk/axstorage.h>

/**
 * disk_item_t represents one storage device and its values.
 */
typedef struct {
    AXStorage* storage;         /** AXStorage reference. */
    AXStorageType storage_type; /** Storage type */
    gchar* storage_id;          /** Storage device name. */
    gchar* storage_path;        /** Storage path. */
    guint subscription_id;      /** Subscription ID for storage events. */
    gboolean setup;             /** TRUE: storage was set up async, FALSE otherwise. */
    gboolean writable;          /** Storage is writable or not. */
    gboolean available;         /** Storage is available or not. */
    gboolean full;              /** Storage device is full or not. */
    gboolean exiting;           /** Storage is exiting (going to disappear) or not. */
} disk_item_t;


/**
 * @brief Guarda la imagen proporcionada en el disco de almacenamiento indicado
 */
gboolean save_image_disk(unsigned char* buffer, disk_item_t* item,  unsigned long buffer_size, const gchar* name);

/**
 * @brief Busca el disco suministradp en la lista de discos disponibles y lo inicializa
 */
disk_item_t* init_disk(gchar* storage_id);


/**
 * @brief Frees disk item
 */
void free_disk_item_t(disk_item_t* item);

/**
 * @brief Subscribes to disk events and creates new disk item
 *
 * @param storage_id storage_id of a disk
 *
 * @return The item
 */
disk_item_t* new_disk_item_t(gchar* storage_id);

