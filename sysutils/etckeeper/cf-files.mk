# $NetBSD: cf-files.mk,v 1.1 2013/05/27 08:36:00 sbd Exp $
#
CF_FILES+= commit.d/10vcs-test
CF_FILES+= commit.d/30bzr-add
CF_FILES+= commit.d/30darcs-add
CF_FILES+= commit.d/30git-add
CF_FILES+= commit.d/30hg-addremove
CF_FILES+= commit.d/50vcs-commit
CF_FILES+= commit.d/99push
CF_FILES+= commit.d/README
CF_FILES+= init.d/10restore-metadata
CF_FILES+= init.d/20restore-etckeeper
CF_FILES+= init.d/40vcs-init
CF_FILES+= init.d/50vcs-ignore
CF_FILES+= init.d/50vcs-perm
CF_FILES+= init.d/50vcs-pre-commit-hook
CF_FILES+= init.d/60darcs-deleted-symlinks
CF_FILES+= init.d/70vcs-add
CF_FILES+= init.d/README
CF_FILES+= list-installed.d/50list-installed
CF_FILES+= post-install.d/50vcs-commit
CF_FILES+= post-install.d/README
CF_FILES+= pre-commit.d/20warn-problem-files
CF_FILES+= pre-commit.d/30store-metadata
CF_FILES+= pre-commit.d/README
CF_FILES+= pre-install.d/10packagelist
CF_FILES+= pre-install.d/50uncommitted-changes
CF_FILES+= pre-install.d/README
CF_FILES+= unclean.d/50test
CF_FILES+= unclean.d/README
CF_FILES+= uninit.d/01prompt
CF_FILES+= uninit.d/50remove-metadata
CF_FILES+= uninit.d/50vcs-uninit
CF_FILES+= uninit.d/README
CF_FILES+= update-ignore.d/01update-ignore
CF_FILES+= update-ignore.d/README
CF_FILES+= vcs.d/50vcs-cmd
