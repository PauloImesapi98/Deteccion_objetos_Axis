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
 * @brief Finds a disk item by its storage_id.
 *
 * @param storage_id The storage_id of the disk item to find.
 * @return The disk item or NULL if not found.
 */
disk_item_t* find_disk_item_t(gchar* storage_id, GList* disks_list);

/**
 * @brief Frees all disk items in the disks list.
 */
void free_disk_item_t(GList* disks_list);

/**
 * @brief Subscribes to disk events and creates new disk item
 *
 * @param storage_id storage_id of a disk
 *
 * @return The item
 */
disk_item_t* new_disk_item_t(gchar* storage_id, GList* disks_list);

